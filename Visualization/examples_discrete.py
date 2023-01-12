from visualize import *
import sys

def example_discrete_ring_graph(n, t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_ring_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Discrete Ring with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_discrete_ring_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_discrete_cos_graph(n, t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_cos_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Discrete cos with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_discrete_cos_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_random_graph(n, t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_random_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Random Graph with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_random_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

if __name__ == "__main__":
    
    steps = np.arange(0, 500, 10)

    # for i in steps:
    #     example_discrete_ring_graph(50, i)
    #     example_discrete_ring_graph(100, i)
    #     example_discrete_ring_graph(250, i)

    # example_discrete_ring_graph(50,   499)
    # example_discrete_ring_graph(100,  499)
    # example_discrete_ring_graph(250,  499)

    # for i in steps:
    #     example_random_graph(100, i)

    n = [50, 100, 150, 200, 250, 300]

    for n_ in n:
        example_discrete_cos_graph(n_,  0)
        example_discrete_cos_graph(n_,  49)


    # for i in steps:
    #     example_discrete_ring_graph(5, i)

    # for i in range(1, 20):
    #     example_discrete_ring_graph(50, i)

