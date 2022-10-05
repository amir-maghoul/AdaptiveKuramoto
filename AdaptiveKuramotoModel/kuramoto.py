""" Module to create adaptive kuramoto model """

import numpy as np
from scipy.integrate import odeint
import typing

class AdaptiveKuramoto():

    def __init__(self, w, K, ro, N=100, t0=0, t_end=40, epsilon=0.01):
        """ Adaptive Kuramoto Class

        Paramters
        ---------
        w : np.ndarray 1D
            the natural frequency

        K : np.ndarray 2D
            the coupling matrix

        ro : float
            the coupling weight

        N : int
            number of oscillators

        t0 : float
            simulation starting time

        t_end : float
            simulation end time

        epsilon : float
            slow dynamics coefficient
        """
        
        self.w = w
        self.K = K
        self.ro = ro
        self.N = N
        self.t0 = t0
        self.T = t_end
        self.epsilon = epsilon

    def dynamics(self, u, alpha, beta):
        """ The ODE dynamcs of the Kuramoto model
            Notice the weight matrix is flattened out and concatenated to the phase vector.
            Therefore the input is a long vector of both phases and weight matrix


            Paramters
            ---------
            u : np.ndarray 1D
                u[0:N] are the phases
                u[N:N**2+N] are the coupling weight matrix flattened out

            alpha : float
                coupling phase lag

            beta : float
                coupling adaptation lag
        """

        # unpacking the inputs
        phi = u[0:self.N]
        A = u[self.N:self.N*self.N+self.N]
        a = alpha*np.ones(self.N)
        b = alpha*np.ones(self.N)

        # create interaction matrix phi_i - phi_j
        interaction = phi[:,None] - phi

        phi_dot = self.w + (self.ro*(A*np.sin(interaction + a)).sum(axis=1)/self.N) 
        A_dot = -self.epsilon(A + np.sin(interaction + b))

        return np.vstack(u, np.reshape(A, (self.N,)))




    def solver(self, u_0, alpha, beta):
        """ Solves the dynamics ODE"""
        return


    def unpack_solver(self):
        pass

    def plot_matrix(self):
        pass

    def plot_phase(self):
        pass

    def order_parameter(self):
        pass

    def plot_order_parameter(self):
        pass


def main():
    u = np.array([1, 2, 3])
    diff = u[:, None] - u
    print(diff)
    print(diff.sum(axis=1))

    

if __name__=="__main__":
    main()