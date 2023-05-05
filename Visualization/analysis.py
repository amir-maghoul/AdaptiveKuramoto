from examples_continuum import *
from examples_discrete import *
from scipy.integrate import trapz
from math import isclose
import numpy.linalg as LA

def weight_comparison(disc_weights, contlim_weights, t, n):
    """The L1 and L2 error of weights"""
    l1_error = np.amax(trapz(np.absolute(contlim_weights[t, :, :] - disc_weights[t, :, :]), axis=1)/n)
    l2_error = LA.norm(contlim_weights[t, :, :] - disc_weights[t, :, :], "fro")
    return l1_error, l2_error

def phi_comparison(disc_phis, contlim_phis, t):
    "The maximum error on phases"
    geodesic_error = np.amax(np.absolute(contlim_phis[t, :] - disc_phis[t, :]))
    return geodesic_error

def total_error(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, error_type="total"):
    """The total error at a specific time"""
    weight_l1_error, weight_l2_error = weight_comparison(disc_weight, contlim_weight, t, n)
    geodesic_error = phi_comparison(disc_phis, contlim_phis, t)
    if error_type == "total":
        return weight_l1_error + geodesic_error, weight_l2_error + geodesic_error
    if error_type == "weights":
        return weight_l1_error, weight_l2_error
    if error_type == "phases":
        return geodesic_error, []

def timewise_max_error(disc_weight, contlim_weight, disc_phis, contlim_phis, num_steps, n, error_type="total"):
    """The maximum of total errors at different times"""
    tvec = np.arange(num_steps)
    l1_timewise_error = np.zeros(len(tvec))
    l2_timewise_error = np.zeros(len(tvec))
    for i, t in enumerate(tvec):
        l1_timewise_error[i], l2_timewise_error[i] = total_error(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, error_type)
    return np.amax(l1_timewise_error), np.amax(l2_timewise_error)

def comparison(n_array, tend, num_steps, t, path, graph_type, error_type="total"):
    """Compare the discrete case and continuum limit"""
    total_l1_error = np.zeros((len(n)))
    total_l2_error = np.zeros((len(n)))
    overall_l1_error = np.zeros((len(n)))
    overall_l2_error = np.zeros((len(n)))

    for i, n_ in enumerate(n_array):
        print(f"n = {n_}" )
        file_loc = path + f"contlim_{graph_type}_with_{n_}_oscillators_tend_{tend}.txt"
        cont_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"contlim_{graph_type}_with_{n_}_oscillators_phases_tend_{tend}.txt"
        cont_phases = read_vector_to_array(file_loc)
        print("contlim data read")

        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_tend_{tend}.txt"
        disc_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_phases_tend_{tend}.txt"
        disc_phases = read_vector_to_array(file_loc)
        print("discrete data read")

        total_l1_error[i], total_l2_error[i] = total_error(disc_weights, cont_weights, disc_phases, cont_phases, t, n_, error_type)
        overall_l1_error[i], overall_l2_error[i] = timewise_max_error(disc_weights, cont_weights, disc_phases, cont_phases, num_steps, n_, error_type)
    return total_l1_error, total_l2_error, overall_l1_error, overall_l2_error

def tend_dependence(tend_array, n_array, path, delay_type, graph_type):
    """ Visualized the dependency of the distance function with respect to end time"""
    distance_l1_matrix = np.zeros((len(tend_array), len(n_array)))
    distance_l2_matrix = np.zeros((len(tend_array), len(n_array)))

    for i, tend_ in enumerate(tend_array):
            print("-------------------------------------------------------")
            print(f"tend = {tend_}")

            loc = path + delay_type + f"tend_{tend_}/"
            _, _, distance_l1_matrix[i, :], distance_l2_matrix[i, :] = comparison(n_array, tend_, 10*tend_, 1, loc, graph_type)

    return distance_l1_matrix, distance_l2_matrix


def discretized_cont_ext_1D(array, N):
    """Creates an array of discretized continuous extension of an array on the interval
    [0, 1]. The aim is to have an array with N elements (view this as discretized interval [0, 1]
    discretized into N elements), which consists of values in the array assigned to each point.
    For this, the function first discretizes the interval by two different 
    discretization fineness, t with length N and t1 with length n=len(array) <= N. Then for each point x
    in t, the function finds to which subinterval of t1, x belongs, then assigns the corresponding value
    of the subinterval from the array to x.
    The function also returns the number of repetitions of each value of array in the final extension.
    This will be used for the 2D case
    
    Parameters
    ----------
    array : np.ndarray
        the array which needs to be extended

    N : int
        the discretization fineness of the continuous extended array


    Returns
    -------
    tuple
        tuple(0) : np.ndarray
            The discretized continuous extension of the input array

        tuple(1) : np.ndarray (len = len(array))
            The number of repetition of each element of array in the final 
            discretized continuous extension
    
    """
    t = np.linspace(0, 1, N)
    n = len(array)
    t1 = np.linspace(0, 1, n+1)
    repetition_array = np.zeros((n), dtype=np.int64)
    cont_extension = np.ones(len(t))
    for i in range(1, len(t1)):
        idx = np.where((t < t1[i]) & (t >= t1[i-1]))[0]
        cont_extension[idx] = array[i-1]*cont_extension[idx]
        repetition_array[i-1] = len(idx)
    cont_extension[-1] = array[-1]
    repetition_array[-1] += 1
    return cont_extension, repetition_array

def discretized_cont_ext_2D(matrix, N):
    """Compute discretized continuous extension of the input matrix on the box [0,1]x[0,1].
    The result is an NxN matrix (view this as the box discretized in N points in each axis).
    The logic is the same as 1D. See discretized_cont_ext_1D.
    The function calls discretized_cont_ext_1D in x-direction. Then uses the repetition array
    output of discretized_cont_ext_1D to copy the values in y-direction.

    Parameters
    ----------
    matrix : np.ndarray 2D
        the matrix which needs to be extended

    N : int
        the number of discretization points of the continuous extension

    Returns
    -------
    np.ndarray of size NxN
        the discretized continous extension 
    """
    t = np.linspace(0, 1, N)
    n = matrix.shape[0]
    _, counts = discretized_cont_ext_1D(matrix[0, :], N)
    repeat_count = np.tile(counts, n)
    temp = matrix.flatten().repeat(repeat_count).reshape((n, N))
    array = temp.repeat(counts, axis=0)
    return array

# What comes below are the same as their counterparts above but this time every one of them are
# computed using the continous extensions. The original ones are needed to compare numerical integration,
# while the functions below are needed to calculate the convergence of discrete system to the continous system

def weight_comparison_with_reference(disc_weights, contlim_weights, t, n, reference_n):
    """The L1 and L2 error of weights"""
    l1_error = np.amax(trapz(np.absolute(contlim_weights[t, :, :] - discretized_cont_ext_2D(disc_weights[t, :, :], reference_n)), axis=1)/n)
    # l2_error = LA.norm(contlim_weights[t, :, :] - discretized_cont_ext_2D(disc_weights[t, :, :], reference_n), "fro")
    return l1_error

def phi_comparison_with_reference(disc_phis, contlim_phis, t, reference_n):
    "The maximum error on phases"
    geodesic_error = np.amax(np.absolute(contlim_phis[t, :] - discretized_cont_ext_1D(disc_phis[t, :], reference_n)[0]))
    return geodesic_error

def total_error_with_reference(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, reference_n, error_type="total"):
    """The total error at a specific time"""
    weight_l1_error = weight_comparison_with_reference(disc_weight, contlim_weight, t, n, reference_n)
    geodesic_error = phi_comparison_with_reference(disc_phis, contlim_phis, t, reference_n)
    if error_type == "total":
        return weight_l1_error + geodesic_error
    if error_type == "weights":
        return weight_l1_error
    if error_type == "phases":
        return geodesic_error
 
def timewise_max_error_with_reference(disc_weight, contlim_weight, disc_phis, contlim_phis, num_steps, n, reference_n, error_type="total"):
    """The maximum of total errors at different times"""
    tvec = np.arange(num_steps)
    l1_timewise_error = np.zeros(len(tvec))
    l2_timewise_error = np.zeros(len(tvec))
    for i, t in enumerate(tvec):
        l1_timewise_error[i] = total_error_with_reference(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, reference_n, error_type)
    return np.amax(l1_timewise_error)

def compare_with_reference(n_array, reference_n, tend, num_steps, path, graph_type, error_type="total"):
    print("Reading data...")
    overall_l1_error = np.zeros((len(n_array)))
    file_loc = path + f"contlim_{graph_type}_with_{reference_n}_oscillators_tend_{tend}.txt"
    cont_weights = read_matrix_to_array(file_loc, reference_n)
    file_loc = path + f"contlim_{graph_type}_with_{reference_n}_oscillators_phases_tend_{tend}.txt"
    cont_phases = read_vector_to_array(file_loc)
    print("contlim data read")

    for i, n_ in enumerate(n_array):
        print(f"n = {n_}" )
        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_tend_{tend}.txt"
        disc_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_phases_tend_{tend}.txt"
        disc_phases = read_vector_to_array(file_loc)
        print("discrete data read")

        overall_l1_error[i] = timewise_max_error_with_reference(disc_weights, cont_weights, disc_phases, cont_phases, num_steps, n_, reference_n, error_type)
    return overall_l1_error



if __name__ == "__main__":

    graph_type = "cos"
    graph_type_raw_data_folder = "ComparisonCos/"
    # graph_type_raw_data_folder = "ComparisonRing/"
    # graph_type_raw_data_folder = "ComparisonErdosReyni/"

    delay_type = "a_0.3pi_b_n0.53pi/"
    # delay_type = "a_0_b_0/"
    error_type = "total"
    reference_n = 250

    tend = 40
    num_steps = tend*10
    n = np.array([5, 10, 25, 50, 100, 150, 200, 250])

    zero_frequency_path = "/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/" + graph_type_raw_data_folder + "ZeroFrequencies/"
    sine_frequency_path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/" + graph_type_raw_data_folder + "SineFrequencies/"

    zero_freq_fileloc = zero_frequency_path + delay_type + f"tend_{tend}/"
    sine_freq_fileloc = sine_frequency_path + delay_type + f"tend_{tend}/"

    path = zero_freq_fileloc

    overall_l1_error = compare_with_reference(n, reference_n, tend, num_steps, path, graph_type, error_type)

    plt.figure()
    print(overall_l1_error)
    plt.loglog(n, overall_l1_error,  "-o", label = "overall l1 error", linewidth=3)
    plot_title = f"Overall error l1 vs l2 norm on weights for tend={tend}" 
    plt.xlabel("Number of oscillators")
    plt.ylabel("Error")
    plt.title(plot_title)
    plt.grid(visible=True, which="both")
    plt.legend()


    # # plt.figure()
    # # plt.semilogy(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
    # # plt.semilogy(n, overall_l2_error, label = "overall l2 error", linestyle= "dotted", linewidth=3)
    # # plot_title = f"Overall error l1 vs l2 norm on weights for tend={tend}" 
    # # plt.xlabel("Number of oscillators")
    # # plt.ylabel("Error")
    # # plt.title(plot_title)
    # # plt.grid(visible=True, which="both")
    # # plt.legend()

    plt.show()
    

    # y = continuous_extension(x, 50)
    # print(y)
    # tend = 40
    # graph_type = "erdos_reyni"
    # delay_type = "a_0.3pi_b_n0.53pi/"
    # delay_type = "a_0_b_0/"

    # path = f"/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/SineFrequencies/"
    # path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonRing/SineFrequencies/"
    # path = "/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonErdosReyni/SineFrequencies/"

    # path = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonRing/SineFrequencies/" + delay_type + f"tend_{tend}/"
    # path = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/SineFrequencies/" + delay_type + f"tend_{tend}/"
    # path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonErdosReyni/SineFrequencies/" + delay_type + f"tend_{tend}/"


    # path = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/tend_{tend}/"


    # error_type = "total"
    # t = 1
    # num_steps = tend*10
    # n = np.array([3, 5, 7, 10, 15, 20, 25, 30, 50, 100, 150, 200, 250])
    # # n = np.array([25, 30, 50, 100, 150, 200, 250, 300, 350, 400])#, 500])
    # total_l1_error, total_l2_error, overall_l1_error, overall_l2_error = comparison(n, tend, num_steps, t, path, graph_type, error_type)

    # plt.figure()
    # plt.plot(n, total_l1_error, label= "total l1 error", linestyle= "dotted", linewidth=3)
    # plt.plot(n, total_l2_error, label = "total l2 error", linestyle= "dotted", linewidth=3)
    # plot_title = f"Total l1 vs l2 error on weights for t = {(t+1)*tend/num_steps}"
    # plt.xlabel(f"Number of oscillators for tend={tend}")
    # plt.ylabel("Error")
    # plt.title(plot_title)
    # plt.grid(visible=True, which="both")
    # plt.legend()

    # plt.figure()
    # plt.semilogy(n, total_l1_error, label="total l1 error", linestyle= "dotted", linewidth=3)
    # plt.semilogy(n, total_l2_error, label = "total l2 error", linestyle= "dotted", linewidth=3)
    # plot_title = f"Total error for l1 vs l2 norm on weights for t = {(t+1)*tend/num_steps}"
    # plt.xlabel(f"Number of oscillators")
    # plt.ylabel("Error")
    # plt.title(plot_title)
    # plt.grid(visible=True, which="both")
    # plt.legend()

    # plt.figure()
    # plt.loglog(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
    # plt.loglog(n, overall_l2_error, label = "overall l2 error", linestyle= "dotted", linewidth=3)
    # plot_title = f"Overall error l1 vs l2 norm on weights for tend={tend}" 
    # plt.xlabel("Number of oscillators")
    # plt.ylabel("Error")
    # plt.title(plot_title)
    # plt.grid(visible=True, which="both")
    # plt.legend()

    # plt.figure()
    # plt.semilogy(n, total_l1_error, label="total l1 error", linestyle= "dotted", linewidth=3)
    # plt.semilogy(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
    # plot_title = f"Overall vs Total error for l1 norm on weights for t = {(t+1)*tend/num_steps}"
    # plt.xlabel("Number of oscillators")
    # plt.ylabel("Error")
    # plt.title(plot_title)
    # plt.grid(visible=True, which="both")
    # plt.legend()

    n = np.array([3, 5, 7, 10, 15, 20, 25, 30, 50, 100, 150, 200])
    tend_array = np.array([5, 10, 20, 40, 50, 75, 100, 150, 200, 300, 500])#, 750])#, 1000])
    # path = f"/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/SineFrequencies/"
    # path = "/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonRing/SineFrequencies/"
    # path = "/media/amir/Elements/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonErdosReyni/SineFrequencies/"

    # path = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/SineFrequencies/"
    # path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonRing/SineFrequencies/"
    # path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonErdosReyni/SineFrequencies/"

    # distance_l1_matrix, distance_l2_matrix = tend_dependence(tend_array, n, path, delay_type, graph_type)

    # plt.figure()
    # for i in range(distance_l1_matrix.shape[0]):
    #     plt.loglog(n, distance_l1_matrix[i, :], linestyle= "dotted", linewidth=3, label=f"tend={tend_array[i]}")
    # plt.xlabel("Number of Oscillators")
    # plt.ylabel("Error")
    # plt.grid(visible=True, which="both")
    # plt.legend()
    # plt.title("Overall Error for different end time for " + delay_type)

    # plt.figure()
    # for i in range(len(tend_array)):
    #     plt.loglog(n, np.absolute(distance_l1_matrix[i,:] - distance_l1_matrix[0,:]), linestyle= "dotted", linewidth=3)
    # plt.xlabel("Number of Oscillators")
    # plt.ylabel("Error Difference")
    # plt.grid(visible=True, which="both")
    # plt.title("Error Difference between first end time with the rest for " + delay_type)

    # plt.figure()
    # im = plt.imshow(distance_l1_matrix, norm = "linear", origin="lower", cmap="copper_r", extent=[n[0], n[-1], tend_array[0], tend_array[-1]], aspect="auto")
    # plt.xlabel("Number of Oscillators")
    # plt.ylabel("End time")
    # plt.title("Error with respect to number of oscillators and time for " + delay_type)
    # plt.colorbar(im)

    # plt.show()




