from visualize import *
import sys

def example_discrete_ring_graph(n, t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_ring_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Ring Graph with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_discrete_ring_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

if __name__ == "__main__":
    
    steps = np.arange(0, 500, 10)

    for i in steps:
        example_discrete_ring_graph(50, i)
        example_discrete_ring_graph(100, i)
        example_discrete_ring_graph(250, i)

    example_discrete_ring_graph(50,   499)
    example_discrete_ring_graph(100,  499)
    example_discrete_ring_graph(250,  499)


    # example_plot_phases()
    # example_plotmatrix_not_so_large_data_positive_ab()
    # example_autonamted_all(100, 50)
    # example_automated_order_parameter()
    # example_plotmatrix_large_data_positive_ab()