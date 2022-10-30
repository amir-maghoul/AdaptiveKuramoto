from visualize import *

def example1():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/alphaPbetaP.txt"
    n = 100
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, 100)

def example2():
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/alphaPbetaP.txt"
    order_parameter = read_vector_to_array(file_loc, n)

if __name__ == "__main__":
    print("main")