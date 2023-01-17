import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import trapz
import sys


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
    adj_matrix = x.reshape(x.shape[0], n, n, order="F")
    return adj_matrix

def plot_matrix(matrix, t, reshuffle_ind=None):
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
    if reshuffle_ind is not None:
        reshuffle_cols = matrix[t, :, reshuffle_ind]
        reshuffle_rows = reshuffle_cols[:, reshuffle_ind]
        im = plt.imshow(reshuffle_rows, origin="lower", cmap="copper_r")
    else:
        im = plt.imshow(matrix[t, :, :], origin="lower", cmap="copper_r")
    plt.colorbar(im)
    plt.title(f"Adjacency Matrix at timestep {t} with jumps")

def plot_phases(phases, osc_number, dt):
    freq = np.zeros((phases.shape[0]-1, phases.shape[1]))
    for i in range(phases.shape[1]):
        freq[:, i] = np.diff(phases[:, i])/dt
    plt.plot(freq[:, osc_number])
    plt.grid("True")
    plt.show()

def reshuffle(phases, window_size, dt, timestep):
    """ Reshuffles the outputs by sorting order
    First sorts the phases by mean frequency (wrt the window size)
    and then sorts each frequency cluster by phases order
    
    Parameters
    ----------
    phases : np.ndarray
        the 2D array of phases after the simulation.
        axis = 0 is the phases of each oscillator at each timestep
        axis = 1 is the simulation result for each timestep

    window_size : int
        the window size from which the mean frequency is calculated

    dt : float
        the solver step

    timestep : int
        the time at which the reshuffling must be considered

    Returns
    -------
    np.ndarray
        The reshuffled array at the timestep
    """
    n = phases.shape[1]
    roll = np.roll(phases, window_size, axis=0)
    freq = (phases - roll)/(dt*window_size)
    sort_freq_index = np.argsort(freq, axis=1) #sort from high to low
    sorted_freq = np.take_along_axis(abs(freq), sort_freq_index, axis=1)

    cluster_bounds = np.where(abs(np.diff(sorted_freq[timestep,:])) > 1)
    cluster_bounds = np.concatenate([[0],cluster_bounds[0], [-1]]) # frequency clusters indices
    # for i in range(len(cluster_bounds)-1):
    #     slice = sort_freq_index[timestep, cluster_bounds[i]:cluster_bounds[i+1]] # Indices of frequency clusters
    #     cluster = slice[np.argsort(phases[timestep, slice])] # sorts the slice by phase order and then return the indices of sorted in the slice
    #     sort_freq_index[timestep, cluster_bounds[i]:cluster_bounds[i+1]] = cluster
    return sort_freq_index[timestep, :]

def plot_order_parameter(array):
    """ Plots evolution of order parameter with respect to t """
    plt.figure()
    plt.title("Order Parameter")
    plt.plot(array)

if __name__ == "__main__":  
    n = 100
    np.set_printoptions(precision=7)

    x = [[[1, 2, 3], [4, 5, 6]], [[2, 3, 4], [4, 5, 6]]]
    print(trapz(x, axis=(1, 2)))
    

    # np.set_printoptions(precision=5,threshold=sys.maxsize)
    # file_loc1 = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_random_with_{n}_oscillators_phases.txt"
    # file_loc2 = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_random_with_{n}_oscillators.txt"
    # phases = read_vector_to_array(file_loc1)
    # matrix = read_matrix_to_array(file_loc2, n)
    # # plot_phases(phases, 0, 0.1)


    # ind = reshuffle(phases, 50, 0.1, 499)
    # plot_matrix(matrix, 499, ind)
    # plt.show()

    # file_loc2 = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_cos_with_50_oscillators.txt"
    # file = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/test_phases_50_oscillators_phases.txt"

    # matrix = read_matrix_to_array(file_loc2, 50)
    # print(matrix[0, :, :])



    


        

