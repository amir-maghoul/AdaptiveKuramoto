from examples_continuum import *
from examples_discrete import *
from scipy.integrate import trapz
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

def _continuous_extension1D(array, N):
    n = len(array)
    partition_length = int(N/n)
    extension = np.repeat(array, partition_length)
    # If the n does not divide N, add one element to each partition until 
    # the gap in difference is filled and an array of N elements is created
    if len(extension) < N:
        len_diff = N - len(extension)
        diff = 0
        temp = extension
        while diff < len_diff:
            temp = np.insert(temp, diff*partition_length + diff, extension[diff*partition_length])
            diff += 1
    extension = temp
    return extension

def _continuous_extension2D(matrix, N):
    if matrix.shape[0] != matrix.shape[1]:
        raise ValueError("2D continuous extension is only defined on square matrices")
    n = matrix.shape[0]
    partition_length = int(N/n)
    extension = np.repeat(matrix, partition_length, axis=0)
    extension = np.repeat(extension, partition_length, axis=1)
    # If the n does not divide N, add one row and column to each partition until 
    # the gap in difference is filled and a matrix of NxN elements is created 
    if len(extension) < N:
        len_diff = N - extension.shape[0]
        diff = 0
        temp = extension
        while diff < len_diff:
            temp = np.insert(temp, diff*partition_length + diff, temp[diff*partition_length + diff, :], axis=0)
            temp = np.insert(temp, diff*partition_length + diff, temp[:, diff*partition_length + diff], axis=1)
            diff += 1
        extension = temp
    return extension

def continuous_extension(matrix, N):
    if matrix.ndim == 1:
        return _continuous_extension1D(matrix, N)
    else:
        return _continuous_extension2D(matrix, N)



if __name__ == "__main__":


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




