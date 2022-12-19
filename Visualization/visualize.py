import numpy as np
import matplotlib.pyplot as plt


def read_vector_to_array(file_loc):
    """
    Reads the vector in file_loc and stores in a numpy array
    """
    matrix_list = []
    with open(file_loc, "r") as f: 
        for line in f:
            matrix_list.append([float(x) for x in line[:-2].split(",")])
    adj_matrix = np.array(matrix_list)
    return adj_matrix

def read_matrix_to_array(file_loc, n):
    """
    Reads the flattend matrix in file_loc and reshapes with respect to n and stores in a numpy array
    """
    matrix_list = []
    with open(file_loc, "r") as f: 
        for line in f:
            matrix_list.append([float(x) for x in line[:-2].split(",")])
    x = np.array(matrix_list)
    adj_matrix = x.reshape(x.shape[0], n, n)
    return adj_matrix

def plot_matrix(matrix, t):
    """Plots the evolution of the adjacency matrix at timestep t
    
    Parameters
    ----------
    matrix : np.ndarray
        3D array of evolution of the adjacency matrix

    t : int 
        the timestep at which the plot is being done
    """
    plt.figure()
    plt.rcParams["figure.figsize"] = [5.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    im = plt.imshow(matrix[t, :, :], cmap="copper_r")
    plt.colorbar(im)
    plt.title(f"Adjacency Matrix at timestep {t} with jumps")

def plot_order_parameter(array):
    """ Plots evolution of order parameter with respect to t"""
    plt.figure()
    plt.title("Order Parameter")
    plt.plot(array)

def visualize_order_parameter(array, t):
    """ Visualizes order parameter at time t on a unit sphere"""
    return
    


        

