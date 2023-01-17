from examples_continuum import *
from examples_discrete import *
from scipy.integrate import trapz
import numpy.linalg as LA

def weight_comparison(disc_weights, contlim_weights, t, n):
    l1_error = np.amax(trapz(np.absolute(contlim_weights[t, :, :] - disc_weights[t, :, :]), axis=1)/n)
    l2_error = LA.norm(contlim_weights[t, :, :] - disc_weights[t, :, :], "fro")
    return l1_error, l2_error

def phi_comparison(disc_phis, contlim_phis, t):
    geodesic_error = np.amax(np.absolute(contlim_phis[t, :] - disc_phis[t, :]))
    return geodesic_error

def total_error(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, error_type="total"):
    weight_l1_error, weight_l2_error = weight_comparison(disc_weight, contlim_weight, t, n)
    geodesic_error = phi_comparison(disc_phis, contlim_phis, t)
    if error_type == "total":
        return weight_l1_error + geodesic_error, weight_l2_error + geodesic_error
    if error_type == "weights":
        return weight_l1_error, weight_l2_error
    if error_type == "phases":
        return geodesic_error, []

def timewise_max_error(disc_weight, contlim_weight, disc_phis, contlim_phis, num_steps, n, error_type="total"):
    tvec = np.arange(num_steps)
    l1_timewise_error = np.zeros(len(tvec))
    l2_timewise_error = np.zeros(len(tvec))
    for i, t in enumerate(tvec):
        l1_timewise_error[i], l2_timewise_error[i] = total_error(disc_weight, contlim_weight, disc_phis, contlim_phis, t, n, error_type)
    return np.amax(l1_timewise_error), np.amax(l2_timewise_error)

def comparison(n, tend, num_steps, t, path="/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/", error_type="total"):
    total_l1_error = np.zeros((len(n)))
    total_l2_error = np.zeros((len(n)))
    overall_l1_error = np.zeros((len(n)))
    overall_l2_error = np.zeros((len(n)))

    for i, n_ in enumerate(n):
        print(f"n = {n_}" )
        file_loc = path + f"contlim_cos_with_{n_}_oscillators_tend_{tend}.txt"
        cont_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"contlim_cos_with_{n_}_oscillators_phases_tend_{tend}.txt"
        cont_phases = read_vector_to_array(file_loc)
        print("contlim data read")

        file_loc = path + f"discrete_cos_with_{n_}_oscillators_tend_{tend}.txt"
        disc_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"discrete_cos_with_{n_}_oscillators_phases_tend_{tend}.txt"
        disc_phases = read_vector_to_array(file_loc)
        print("discrete data read")

        total_l1_error[i], total_l2_error[i] = total_error(disc_weights, cont_weights, disc_phases, cont_phases, t, n_, error_type)
        overall_l1_error[i], overall_l2_error[i] = timewise_max_error(disc_weights, cont_weights, disc_phases, cont_phases, num_steps, n_, error_type)
    return total_l1_error, total_l2_error, overall_l1_error, overall_l2_error


if __name__ == "__main__":
    path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/"
    error_type = "total"
    t = 399
    num_steps = 400
    tend = 40
    n = [3, 5, 7, 10, 15, 20, 25, 30, 50, 100, 150] #[200, 250, 300, 350, 400, 500]
    # n = [25, 30, 50, 100, 150]
    total_l1_error, total_l2_error, overall_l1_error, overall_l2_error = comparison(n, tend, num_steps, t, path, error_type)

    plt.figure()
    plt.semilogy(n, total_l1_error, label="total l1 error", linestyle= "dotted", linewidth=3)
    plt.semilogy(n, total_l2_error, label = "total l2 error", linestyle= "dotted", linewidth=3)
    plot_title = f"Total error for l1 vs l2 norm on weights for t = {(t+1)*tend/num_steps}"
    plt.title(plot_title)
    plt.grid(visible=True, which="both")
    plt.legend()

    plt.figure()
    plt.semilogy(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
    plt.semilogy(n, overall_l2_error, label = "overall l2 error", linestyle= "dotted", linewidth=3)
    plot_title = "Overall error l1 vs l2 norm on weights" 
    plt.title(plot_title)
    plt.grid(visible=True, which="both")
    plt.legend()

    plt.figure()
    plt.semilogy(n, total_l1_error, label="total l1 error", linestyle= "dotted", linewidth=3)
    plt.semilogy(n, overall_l1_error, label = "overall l1 error", linestyle= "dotted", linewidth=3)
    plot_title = f"Overall vs Total error for l1 norm on weights for t = {(t+1)*tend/num_steps}"
    plt.title(plot_title)
    plt.grid(visible=True, which="both")
    plt.legend()

    plt.show()




