from visualize import *
import sys

d
def example_autonamted_all(n, t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/clustering_file.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/order_parameter_file.txt"
    order_parameter = read_vector_to_array(file_loc)
    plot_matrix(adj_matrix, t)
    plot_order_parameter(order_parameter)
    plt.show()

def example_automated_order_parameter():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/order_parameter_file.txt"
    order_parameter = read_vector_to_array(file_loc)
    plot_order_parameter(order_parameter)
    plt.show()

def example_plotmatrix_large_data_positive_ab():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/alphaPbetaP.txt" # 10000 end time with 100000 timesteps
    n = 100
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, 100)
    plt.show()

def example_plotmatrix_not_so_large_data_positive_ab():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/a0_3p_b0_53p.txt" # 1000 end time with 10000 timesteps
    adj_matrix = read_matrix_to_array(file_loc, 100)
    plot_matrix(adj_matrix, 1)
    plt.show()

def example_plot_phases():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/phases_file.txt"
    phases = read_vector_to_array(file_loc)
    plt.plot(np.diff(phases[:, 1])/0.01)
    plt.show()

if __name__ == "__main__":
    timestep = 100
    n = 50
    # example_plot_phases()
    # example_plotmatrix_not_so_large_data_positive_ab()
    # example_autonamted_all(100, 50)
    # example_automated_order_parameter()
    # example_plotmatrix_large_data_positive_ab()