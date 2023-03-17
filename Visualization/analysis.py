from examples_continuum import *
from examples_discrete import *
from scipy.integrate import trapz
import numpy.linalg as LA
from numba import njit

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





def continuous_extension1D(x, array):
    n = len(array)
    t = np.linspace(0, 1, n+1)
    if x == 0:
        return array[0]
    if x == 1:
        return array[-1]
    if any(t < x):
        return array[max(np.where(t < x)[0])]
    else:
        raise ValueError("The given x is not in the [0, 1] interval ")

def continuous_extension2D(x, y, array):
    n = array.shape[0]
    t = np.linspace(0, 1, n+1)
    if x == 1 and y != 1:
        return array[-1, max(np.where(t <= y)[0])]
    elif x != 1 and y == 1:
        return array[max(np.where(t <= x)[0]), -1]
    elif x == 1 and y == 1:
        return array[-1, -1]
    else:
        return array[max(np.where(t <= x)[0]), max(np.where(t <= y)[0])]

def discretize(fun, N, dim):
    t = np.linspace(0, 1, N)
    if dim == 1:
        return np.array([fun(x) for x in t])
    elif dim == 2:
        return np.array([fun(x, y) for x in t for y in t]).reshape((len(t), len(t)))
    else:
        raise ValueError("The input dimension can only be 1 or 2")

def discretized_continuous_extension(matrix, N):
    if matrix.ndim == 1:
        f = lambda x : continuous_extension1D(x, matrix)
    else:
        if matrix.shape[0] != matrix.shape[1]:
            raise ValueError("The weights of the discrete system must be a square matrix")
        f = lambda x, y : continuous_extension2D(x, y, matrix)
    result = discretize(f, N, matrix.ndim)
    return result

def discretized_cont_ext_1D(matrix, N):
        t = np.linspace(0, 1, N)
        n = len(matrix)
        t1 = np.linspace(0, 1, n+1)
        index_array = np.zeros((n), dtype=np.int64)
        array = np.ones(len(t))
        for i in range(1, len(t1)):
            idx = np.where((t < t1[i]) & (t >= t1[i-1]))[0]
            array[idx] = matrix[i-1]*array[idx]
            index_array[i-1] = len(idx)
        array[-1] = matrix[-1]
        index_array[-1] += 1
        return array, index_array

def discretized_cont_ext_2D(matrix, N):
    t = np.linspace(0, 1, N)
    n = matrix.shape[0]
    _, counts = discretized_cont_ext_1D(matrix[0, :], N)
    repeat_count = np.tile(counts, n)
    temp = matrix.flatten().repeat(repeat_count).reshape((n, N))
    array = temp.repeat(counts, axis=0)
    return array


# def continuous_extension3D(matrix, N):
#     copy = np.zeros((matrix.shape[0], N, N))
#     for i in range(copy.shape[0]):
#         copy[i, :, :] = discretized_continuous_extension2(matrix[i, :, :], N)
#     return copy
# def cont(aim_t_array, array):
#     xx, yy = np.meshgrid(aim_t_array, aim_t_array)
#     aim = np.zeros(xx.shape)
#     n = array.shape[0]
#     t = np.linspace(0, 1, n+1)
#     for i in range(0, len(t)):
#         for j in range(0, len(t)):
#             idx1 = (xx < t1[i]) & (xx >= t1[i-1])
#             idx2 = (yy < t1[j]) & (yy >= t1[j-1])
#             idx = np.logical_and(idx1, idx2).nonzero()
#             aim[idx] = array[j-1, i-1]
#     aim[:, -1] = aim[:, -2]
#     aim[-1, :] = aim[-2, :]
#     return aim

    




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
    overall_l1_error = np.zeros((len(n)))
    overall_l2_error = np.zeros((len(n)))
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

        # disc_weights = discritized_continuous_extension(disc_weights, reference_n)
        # disc_phases = discritized_continuous_extension(disc_phases, reference_n)

        # total_l1_error[i], total_l2_error[i] = total_error(disc_weights, cont_weights, disc_phases, cont_phases, t, n_, error_type)
        overall_l1_error[i] = timewise_max_error_with_reference(disc_weights, cont_weights, disc_phases, cont_phases, num_steps, n_, reference_n, error_type)
    # return total_l1_error, total_l2_error, overall_l1_error, overall_l2_error
    return overall_l1_error



if __name__ == "__main__":
    n = 3
    N = 7
    x = np.arange(n)+1
    # x = np.array([1, 2, 3, 4, 1, 5, 7, 1, 8])
    # # x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    # x = np.arange(0, n*n).reshape((n, n))
    # print(x)
    t1 = np.linspace(0, 1, n+1)
    t2 = np.linspace(0, 1, N)
    # tt, ff = np.meshgrid(t2, t2)
    # print(tt < t1[1])
    # print("t1=", t1)
    # print("t2=", t2)
    # def cont(aim_t_array, array):
    #     xx, yy = np.meshgrid(aim_t_array, aim_t_array)
    #     aim = np.zeros(xx.shape)
    #     n = array.shape[0]
    #     t = np.linspace(0, 1, n+1)
    #     for i in range(0, len(t)):
    #         for j in range(0, len(t)):
    #             idx1 = (xx < t1[i]) & (xx >= t1[i-1])
    #             idx2 = (yy < t1[j]) & (yy >= t1[j-1])
    #             idx = np.logical_and(idx1, idx2).nonzero()
    #             aim[idx] = array[j-1, i-1]
    #     aim[:, -1] = aim[:, -2]
    #     aim[-1, :] = aim[-2, :]
    #     return aim

        # if (xx == 1).nonzero() is not None and (yy != 1).nonzero() is not None:
        #     aim[] array[-1, max(np.where(t <= y)[0])]
        # elif x != 1 and y == 1:
        #     return array[max(np.where(t <= x)[0]), -1]
        # elif x == 1 and y == 1:
        #     return array[-1, -1]
        # else:
        #     return array[max(np.where(t <= x)[0]), max(np.where(t <= y)[0])]
        # array[idx1, idx2] = x[i-1]*array[idx]
    # array[-1, -1] = x[-1, -1]
    # print(array)
    # y = cont(t2, x)
    # print(y)
    # print(discretized_continuous_extension2(x, N))
    # print(discretized_continuous_extension(x, N))

    # y = np.arange(9) + 1
    # y =  np.array([1, 2, 3, 4, 1, 5, 7, 1, 8])
    # print(x)
    # print(discretized_cont_ext_1D(x, 5))
    # print(discretized_cont_ext_2D(y.reshape(3, 3), 5))




    graph_type = "cos"
    delay_type = "a_0.3pi_b_n0.53pi/"
    # delay_type = "a_0_b_0/"
    error_type = "total"
    reference_n = 250

    tend = 300
    num_steps = tend*10
    n = np.array([5, 10, 25, 50, 100, 150])

    path = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/SineFrequencies/" + delay_type + f"tend_{tend}/"
    overall_l1_error= compare_with_reference(n, reference_n, tend, num_steps, path, graph_type, error_type)



    plt.figure()
    plt.loglog(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
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




