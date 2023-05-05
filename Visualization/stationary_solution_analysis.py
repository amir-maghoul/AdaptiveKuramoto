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

def stationary_solution_weights(x, y, b):
    """ Computer the weight values for the exact stationary solutions."""
    return np.sin(x - y + b)


if __name__ == "__main__":

    omega = 0