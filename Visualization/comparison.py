from examples_continuum import *
from examples_discrete import *
import numpy.linalg as LA

if __name__ == "__main__":

    n = [10, 30, 50, 75, 100, 150]
    steps = np.arange(0, 500, 10)

    error_matrix = np.zeros((len(n), 500))

    for i, n_ in enumerate(n):
        file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_ring_with_{n_}_oscillators.txt"
        cont_matrix = read_matrix_to_array(file_loc, n_)

        file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_ring_with_{n_}_oscillators.txt"
        disc_matrix = read_matrix_to_array(file_loc, n_)

        error_matrix[i, :] = LA.norm(cont_matrix - disc_matrix, axis=(1,2)).T
    

    plt.plot(n, error_matrix[:, 2])
    plt.show()

