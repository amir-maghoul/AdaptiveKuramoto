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

    def dynamics(self):
        pass

    def solver(self):
        pass

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


