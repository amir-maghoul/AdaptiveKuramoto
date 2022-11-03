from visualize import *

def example_autonamted_all(n, t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/clustering_file.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/order_parameter_file.txt"
    order_parameter = read_vector_to_array(file_loc)
    plot_matrix(adj_matrix, t)
    plot_order_parameter(order_parameter)
    plt.show()

def example_automated_phase_and_order_parameter():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/order_parameter_file.txt"
    order_parameter = read_vector_to_array(file_loc)
    plot_order_parameter(order_parameter)
    plt.show()

def example_plotmatrix_large_data_positive_ab():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/alphaPbetaP.txt"
    n = 100
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, 100)
    plt.show()

if __name__ == "__main__":
    timestep = 100
    n = 100
    # automated_order_parameter()
    # example_autonamted_all(n, timestep)
    example_automated_phase_and_order_parameter(0)
