""" Module to create adaptive kuramoto model """

import numpy as np
from scipy.integrate import odeint
import typing
import timeit
import matplotlib.pyplot as plt



class AdaptiveKuramoto():

    def __init__(self, w, K0, ro=1, t0=0, t_end=40, dt=0.01, epsilon=0.01):
        """ Adaptive Kuramoto Class

        Paramters
        ---------
        w : np.ndarray 1D
            the natural frequency

        K0 : np.ndarray 2D
            the coupling matrix - initial topology

        ro : float (default=1)
            the coupling weight 

        t0 : float (default=0)
            simulation starting time

        t_end : float (default=40)
            simulation end time

        dt : float (default=0.01)
            the timestep

        epsilon : float (default=0.01)
            slow dynamics coefficient
        """
        
        self.w = w
        self.K0 = K0
        self.ro = ro
        self.N = w.shape[0]
        self.tvec = np.arange(t0, t_end, dt)
        self.t0 = t0
        self.T = t_end
        self.dt = dt
        self.epsilon = epsilon

    def dynamics(self, u, t, a, b):
        """ The ODE dynamcs of the Kuramoto model
            Notice the weight matrix is flattened out and concatenated to the phase vector.
            Therefore the input is a long vector of both phases and weight matrix


        Paramters
        ---------
        u : np.ndarray 1D
            u[0:N] are the phases
            u[N:N**2+N] are the coupling weight matrix flattened out

        a : np.ndarray 1D
            coupling phase lag as vector

        b : np.ndarray 1D
            coupling adaptation lag as vector

        Returns
        -------
        np.ndarray
            
        """

        # unpacking the inputs
        phi = u[0:self.N]
        A = u[self.N:].reshape(self.N, self.N)

        # create interaction matrix phi_j - phi_i
        interaction = phi - phi[:,None]

        phi_dot = self.w + self.ro*np.sum(A*np.sin(interaction + a), axis=1)/self.N
        A_dot = -self.epsilon*(A + np.sin(interaction + b))

        # repacking the output
        u_dot = np.empty(self.N*self.N+self.N)
        u_dot[0:self.N] = phi_dot
        u_dot[self.N:] = A_dot.ravel()

        return u_dot

    def solve(self, u0, alpha=0, beta=0):
        """ Solves the dynamics ODE.
        
        Parameters
        ----------
        u0 : np.ndarray
            initial values
            u0[0:N]= initial phases
            u0[N:]= inital coupling matrix/initial topology flattened

        alpha : float (default=0)
            coupling phase lag as vector

        beta : float (default=0)
            coupling adaptation lag as vector

        Returns
        -------
        np.ndarray
        """
        # packing input
        u = np.empty(self.N*self.N+self.N)
        u[0:self.N] = u0
        u[self.N:] = self.K0.ravel()

        # creating control vectors
        a = alpha*np.ones(self.N)
        b = beta*np.ones(self.N)

        # solving the ode
        kode = odeint(self.dynamics, u, self.tvec, args=(a, b)).T
        return self._unpack_array(kode)

    def _unpack_array(self, array):
        u = array[0:self.N, :]
        A = array[self.N:, :].reshape(self.N, self.N, len(self.tvec))
        return u, A

    def plot_matrix(self):
        pass

    def plot_phase(self):
        pass

    def order_parameter(self):
        pass

    def plot_order_parameter(self):
        pass


def main():

    u0 = np.array([0, np.pi, 0])
    w = np.array([28, 19, 11])
    K0 = np.array([[ 0, 0.2,  1.1],
                    [0.5,   0, -0.7],
                    [0.3, 0.9,    0]])
    
    obj = AdaptiveKuramoto(w, K0, dt=0.1, epsilon=0)
    u, A = obj.solve(u0)
    print(A[:, :, 4])



    

if __name__=="__main__":
    main()