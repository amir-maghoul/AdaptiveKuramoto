import numpy as np
from scipy.integrate import odeint

def kuramoto_model(y, t, eps):
    # y is the vector of phase variables and weight matrix elements
    # t is the time variable
    # eps is the coupling strength parameter

    # Reshape y into the phase and weight matrices
    phi = y[:N]
    w = y[N:].reshape((N, N))

    # Compute the time derivative of phi
    dphi = np.zeros_like(phi)
    for i in range(N):
        dphi[i] = omega[i] + eps * np.sum(w[i, :] * np.sin(phi - phi[i]))

    # Compute the time derivative of w
    dw = -eps * (np.sin(np.subtract.outer(phi, phi)) + w)

    # Combine the time derivatives into a single vector
    dydt = np.concatenate((dphi, dw.reshape(-1)))

    return dydt

# Define the system parameters
N = 3  # Number of oscillators
L = 1.0  # System size
omega = np.zeros(N)  # Natural frequencies
eps = 0.1  # Coupling strength parameter

# Define the initial values for phi and w
dx = L / N
x = np.linspace(0, L, N, endpoint=True)
phi0 = np.pi * x
w0 = -np.sin(np.subtract.outer(np.pi * x, np.pi * x))

# Combine the initial values into a single vector
y0 = np.concatenate((phi0, w0.reshape(-1)))

# Define the time grid for the simulation
t = np.linspace(0, 40, 400)

# Use odeint to solve the ODE
sol = odeint(kuramoto_model, y0, t, args=(eps,))
w_all = sol[:, N:].reshape((len(t), N, N))
print(w_all[-1, :, :])

