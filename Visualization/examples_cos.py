from visualize import *
import sys

def example_small_cos_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_small_cos_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("small cos short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/small_cos_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_small_cos_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_small_cos_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("small cos long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/small_cos_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_large_cos_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_large_cos_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("large cos short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/large_cos_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_large_cos_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_large_cos_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("large cos long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/large_cos_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_quite_large_cos_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_quite_large_cos_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("quite large cos short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/quite_large_cos_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_quite_large_cos_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_quite_large_cos_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("quite large cos long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/quite_large_cos_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_very_large_cos_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_very_large_cos_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("very large cos short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/very_large_cos_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_very_large_cos_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_very_large_cos_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("very large cos long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/very_large_cos_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

if __name__ == "__main__":

    # example_small_cos_graph_short_simulation(50, 999)
    example_small_cos_graph_long_simulation(50, 0)
    example_small_cos_graph_long_simulation(50, 200)
    example_small_cos_graph_long_simulation(50, 250)
    example_small_cos_graph_long_simulation(50, 260)
    example_small_cos_graph_long_simulation(50, 270)
    example_small_cos_graph_long_simulation(50, 280)
    example_small_cos_graph_long_simulation(50, 290)
    example_small_cos_graph_long_simulation(50, 300)
    example_small_cos_graph_long_simulation(50, 310)
    example_small_cos_graph_long_simulation(50, 320)
    example_small_cos_graph_long_simulation(50, 330)
    example_small_cos_graph_long_simulation(50, 340)
    example_small_cos_graph_long_simulation(50, 350)
    example_small_cos_graph_long_simulation(50, 499)

    # example_large_cos_graph_short_simulation(100, 100)
    # example_large_cos_graph_long_simulation(100, 0)
    # example_large_cos_graph_long_simulation(100, 10)
    # example_large_cos_graph_long_simulation(100, 25)
    # example_large_cos_graph_long_simulation(100, 26)
    # example_large_cos_graph_long_simulation(100, 27)
    # example_large_cos_graph_long_simulation(100, 28)
    # example_large_cos_graph_long_simulation(100, 29)
    # example_large_cos_graph_long_simulation(100, 30)
    # example_large_cos_graph_long_simulation(100, 31)
    # example_large_cos_graph_long_simulation(100, 32)
    # example_large_cos_graph_long_simulation(100, 33)
    # example_large_cos_graph_long_simulation(100, 34)
    # example_large_cos_graph_long_simulation(100, 35)
    # example_large_cos_graph_long_simulation(100, 499)

    # example_quite_large_cos_graph_short_simulation(250, 100)
    # example_quite_large_cos_graph_long_simulation(250, 0)
    # example_quite_large_cos_graph_long_simulation(250, 1)
    # example_quite_large_cos_graph_long_simulation(250, 5)
    # example_quite_large_cos_graph_long_simulation(250, 6)
    # example_quite_large_cos_graph_long_simulation(250, 7)
    # example_quite_large_cos_graph_long_simulation(250, 8)
    # example_quite_large_cos_graph_long_simulation(250, 9)
    # example_quite_large_cos_graph_long_simulation(250, 10)
    # example_quite_large_cos_graph_long_simulation(250, 25)
    # example_quite_large_cos_graph_long_simulation(250, 50)
    # example_quite_large_cos_graph_long_simulation(250, 75)
    # example_quite_large_cos_graph_long_simulation(250, 99)

    # example_very_large_cos_graph_short_simulation(500, -1)
    # example_very_large_cos_graph_long_simulation(500, -1)

    # example_very_large_cos_graph_long_simulation(500, 0)
    # example_very_large_cos_graph_long_simulation(500, 1)
    # example_very_large_cos_graph_long_simulation(500, 5)
    # example_very_large_cos_graph_long_simulation(500, 6)
    # example_very_large_cos_graph_long_simulation(500, 7)
    # example_very_large_cos_graph_long_simulation(500, 8)
    # example_very_large_cos_graph_long_simulation(500, 9)
    # example_very_large_cos_graph_long_simulation(500, 10)
    # example_very_large_cos_graph_long_simulation(500, 25)
    # example_very_large_cos_graph_long_simulation(500, 50)
    # example_very_large_cos_graph_long_simulation(500, 75)
    # example_very_large_cos_graph_long_simulation(500, 99)





