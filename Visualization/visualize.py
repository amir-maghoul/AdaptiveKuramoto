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
        reshuffle_cols = matrix[:, :, reshuffle_ind[t,:]]
        reshuffle_rows = reshuffle_cols[:, reshuffle_ind[t,:], :]
        im = plt.imshow(reshuffle_rows[t, :, :], cmap="copper_r")
    else:
        im = plt.imshow(matrix[t, :, :], cmap="copper_r")
    plt.colorbar(im)
    plt.title(f"Adjacency Matrix at timestep {t} with jumps")

def plot_phases(phases, osc_number, dt):
    freq = np.zeros((phases.shape[0]-1, phases.shape[1]))
    for i in range(phases.shape[1]):
        freq[:, i] = np.diff(phases[:, i])/dt;
    plt.plot(freq[:, osc_number])
    plt.show()

def reshuffle(phases, window_size, dt):
    n = phases.shape[1]
    roll = np.roll(phases, window_size, axis=0)
    freq = (phases - roll)/(dt*window_size)
    sort_freq_index = np.argsort(freq, axis=1)
    sorted_freq = np.take_along_axis(freq, sort_freq_index, axis=1)
    return sort_freq_index

def plot_order_parameter(array):
    """ Plots evolution of order parameter with respect to t"""
    plt.figure()
    plt.title("Order Parameter")
    plt.plot(array)


if __name__ == "__main__":
    n = 50
    file_loc1 = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_random_with_{n}_oscillators_phases.txt"
    file_loc2 = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_random_with_{n}_oscillators.txt"
    phases = read_vector_to_array(file_loc1)
    matrix = read_matrix_to_array(file_loc2, n)
    # plot_phases(phases, 0, 0.1)
    ind = reshuffle(phases, 20, 0.1)
    plot_matrix(matrix, 490, ind)
    plt.show()

    


        

