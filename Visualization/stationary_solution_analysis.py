from math import isclose
from scipy.integrate import quad
from analysis import *


def stationary_solution_phi(t, x, omega, phi_tilde, a, b):
    """Compute phase values of the exact stationary solution.
    
    Parameters
    ----------
    t : float
        time at which the solution is evaluated
    x : float
        spatial point at which the solution is evaluated
    Omega : float
        Some constant frequency
    phi_tilde : callable
        A stationary function with second order parameter equal to zero
    a : float
        phase lag
    b : float
        adaptation lag

    Returns
    -------
    float

    """
    real_integrand = lambda x : np.cos(-2*phi_tilde(x))
    im_integrand = lambda x : np.sin(-2*phi_tilde(x))
    real_integral = quad(real_integrand, 0, 1)
    im_integral = quad(im_integrand, 0, 1)

    if not (isclose(im_integral[0], 0, abs_tol=1e-10) and isclose(real_integral[0], 0, abs_tol=1e-10)):
        raise ValueError("The second order parameter of phi_tilde must be zero")
    
    Omega = omega + np.cos(a-b)/2

    return Omega*t + phi_tilde(x)

def stationary_solution_weights(x, y, phi_tilde, b):
    """ Computer the weight values for the exact stationary solutions."""

    return np.sin(phi_tilde(x) - phi_tilde(y) + b)

def discretize_phi(t_array, x_array, omega, phi_tilde, a=0, b=0):
    xx, tt = np.meshgrid(x_array, t_array)
    return stationary_solution_phi(tt, xx, omega, phi_tilde, a, b)

def discretize_weights(x_array, y_array, phi_tilde, b=0):
    xx, yy = np.meshgrid(x_array, y_array)
    return stationary_solution_weights(xx, yy, phi_tilde, b)


def exact_compare_with_reference(contlim_data, n_array, reference_n, tend, num_steps, path):
    print("Creaating Continuum Limit Data...")
    graph_type = "exact"
    error_type = "total"
    omega = contlim_data[0]
    a = contlim_data[1]
    b = contlim_data[2]
    phi_tilde = contlim_data[3]

    t = np.linspace(0, tend, num_steps)
    x = y = np.linspace(0, 1, reference_n)

    weights = discretize_weights(x, y, phi_tilde, b)
    cont_weights = np.tile(weights, (num_steps, 1, 1))
    cont_phases = discretize_phi(t, x, omega, phi_tilde, a, b)
    print("Done")

    print("Reading discrete data...")

    overall_l1_error = np.zeros((len(n_array)))

    for i, n_ in enumerate(n_array):
        print(f"n = {n_}" )
        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_tend_{tend}.txt"
        disc_weights = read_matrix_to_array(file_loc, n_)
        file_loc = path + f"discrete_{graph_type}_with_{n_}_oscillators_phases_tend_{tend}.txt"
        disc_phases = read_vector_to_array(file_loc)
        print(f"{i}th discrete data read")

        overall_l1_error[i] = timewise_max_error_with_reference(disc_weights, cont_weights, disc_phases, cont_phases, num_steps, n_, reference_n, error_type)
    return overall_l1_error




if __name__ == "__main__":

    omega = 0
    a = 0
    b = 0   
    phi_tilde = lambda x : np.pi*x
    contlim_data = (omega, a, b, phi_tilde)
    tend = 40
    num_steps = tend*100
    reference_n = 200
    N = [3, 5, 7, 10, 15, 20, 25, 30, 50, 100, 150, 200]#, 300, 350]
    path = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/"

    # file_loc = path + f"discrete_exact_with_3_oscillators_tend_40.txt"
    # disc_weights = read_matrix_to_array(file_loc, 3)



    overall_l1_error = exact_compare_with_reference(contlim_data, N, reference_n, tend, num_steps, path)

    plt.figure()
    plt.loglog(N, overall_l1_error,  "-o", label = "overall l1 error", linewidth=3)
    plot_title = f"Overall error with l1 norm on weights for tend={tend} of exact solution" 
    plt.xlabel("Number of oscillators")
    plt.ylabel("Error")
    plt.title(plot_title)
    plt.grid(visible=True, which="both")
    plt.legend()

    plt.show()

