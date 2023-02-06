from visualize import *
import sys

def example_contlim_ring_graph(n ,t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_ring_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Contlim Ring with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_contlim_ring_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_contlim_cos_graph(n ,t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/tend_1000/contlim_cos_with_{n}_oscillators_tend_1000.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Sinusoidal Graph with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_contlim_cos_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_contlim_gauss_graph(n ,t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_gauss_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Contlim Ring with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_contlim_gauss_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_contlim_random_graph(n, t):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_random_with_{n}_oscillators.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Random Graph with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_random_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_contlim_erdos_reyni_graph(n ,t, tend):
    file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_erdos_reyni_with_{n}_oscillators_tend_{tend}.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title(f"Erdos Reyni Graph with {n} Oscillators")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/"+str(n)+"_oscillators_contlim_erdos_reyni_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

if __name__ == "__main__":

    steps = np.arange(0, 500, 10)
    steps_small = np.arange(0, 200, 10)

    t = [0, 1, 10, 99, 999, 9999]

    for t_ in t:
        example_contlim_erdos_reyni_graph(50, t_, 1000)

    # for i in steps:
        
    #     example_contlim_ring_graph(50, i)
    #     example_contlim_ring_graph(100, i)
    #     example_contlim_ring_graph(250, i)

    # example_contlim_ring_graph(50, 499)
    # example_contlim_ring_graph(100, 499)
    # example_contlim_ring_graph(250, 499)

    n = [50, 100, 150, 200, 250, 300]

    # for n_ in n:
    #     example_contlim_cos_graph(n_,  0)
    #     example_contlim_cos_graph(n_,  49)

    # example_contlim_cos_graph(50, 999)

    # for i in steps:
    #     example_contlim_ring_graph(5, i)

    # for i in range(70, 90):
    #     example_contlim_ring_graph(5, i)
