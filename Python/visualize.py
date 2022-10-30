import numpy as np
import matplotlib.pyplot as plt


def read_vector_to_array(file_loc, vector):
    matrix_list = []
    with open(file_loc, "r") as f: 
        for line in f:
            matrix_list.append([float(x) for x in line[:-2].split(",")])
    adj_matrix = np.array(matrix_list)
    return adj_matrix

def read_matrix_to_array(file_loc, n):
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
    plt.rcParams["figure.figsize"] = [7.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    im = plt.imshow(matrix[t, :, :], cmap="copper_r")
    plt.colorbar(im)
    plt.show()


if __name__ == "__main__":
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/vector_file.txt"
    n = 100
    adj_matrix = read_matrix_to_array(file_loc, n)
    # print(adj_matrix[0])
    plot_matrix(adj_matrix, 110)

        

