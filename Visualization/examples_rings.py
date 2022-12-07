from visualize import *
import sys

def example_small_ring_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_small_ring_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("small ring short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/small_ring_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_small_ring_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_small_ring_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("small ring long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/small_ring_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_large_ring_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_large_ring_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("large ring short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/large_ring_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_large_ring_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_large_ring_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("large ring long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/large_ring_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_quite_large_ring_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_quite_large_ring_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("quite large ring short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/quite_large_ring_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_quite_large_ring_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_quite_large_ring_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("quite large ring long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/quite_large_ring_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_very_large_ring_graph_short_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_very_large_ring_graph_short_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("very large ring short")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/very_large_ring_short_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

def example_very_large_ring_graph_long_simulation(n ,t):
    file_loc = "/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_very_large_ring_graph_long_simulation.txt"
    adj_matrix = read_matrix_to_array(file_loc, n)
    plot_matrix(adj_matrix, t)
    plt.title("very large ring long")
    fig_name = "/home/amir/AdaptiveKuramoto/KuramotoModel/Figures/very_large_ring_long_at_time_"+str(t)+".png"
    plt.savefig(fig_name, dpi=500)
    plt.close()

if __name__ == "__main__":

    # example_small_ring_graph_short_simulation(50, 999)
    example_small_ring_graph_long_simulation(50, 0)
    example_small_ring_graph_long_simulation(50, 10)
    example_small_ring_graph_long_simulation(50, 20)
    example_small_ring_graph_long_simulation(50, 30)
    example_small_ring_graph_long_simulation(50, 40)
    example_small_ring_graph_long_simulation(50, 50)
    example_small_ring_graph_long_simulation(50, 60)
    example_small_ring_graph_long_simulation(50, 70)
    example_small_ring_graph_long_simulation(50, 80)
    example_small_ring_graph_long_simulation(50, 90)
    example_small_ring_graph_long_simulation(50, 100)
    example_small_ring_graph_long_simulation(50, 110)
    example_small_ring_graph_long_simulation(50, 120)
    example_small_ring_graph_long_simulation(50, 130)
    example_small_ring_graph_long_simulation(50, 140)
    example_small_ring_graph_long_simulation(50, 150)
    example_small_ring_graph_long_simulation(50, 160)
    example_small_ring_graph_long_simulation(50, 170)
    example_small_ring_graph_long_simulation(50, 180)
    example_small_ring_graph_long_simulation(50, 190)
    example_small_ring_graph_long_simulation(50, 200)
    example_small_ring_graph_long_simulation(50, 210)
    example_small_ring_graph_long_simulation(50, 220)
    example_small_ring_graph_long_simulation(50, 230)
    example_small_ring_graph_long_simulation(50, 240)
    example_small_ring_graph_long_simulation(50, 250)
    example_small_ring_graph_long_simulation(50, 260)
    example_small_ring_graph_long_simulation(50, 270)
    example_small_ring_graph_long_simulation(50, 280)
    example_small_ring_graph_long_simulation(50, 290)
    example_small_ring_graph_long_simulation(50, 300)
    example_small_ring_graph_long_simulation(50, 310)
    example_small_ring_graph_long_simulation(50, 320)
    example_small_ring_graph_long_simulation(50, 330)
    example_small_ring_graph_long_simulation(50, 340)
    example_small_ring_graph_long_simulation(50, 350)
    example_small_ring_graph_long_simulation(50, 360)
    example_small_ring_graph_long_simulation(50, 370)
    example_small_ring_graph_long_simulation(50, 380)
    example_small_ring_graph_long_simulation(50, 390)
    example_small_ring_graph_long_simulation(50, 400)
    example_small_ring_graph_long_simulation(50, 410)
    example_small_ring_graph_long_simulation(50, 420)
    example_small_ring_graph_long_simulation(50, 430)
    example_small_ring_graph_long_simulation(50, 440)
    example_small_ring_graph_long_simulation(50, 450)
    example_small_ring_graph_long_simulation(50, 460)
    example_small_ring_graph_long_simulation(50, 470)
    example_small_ring_graph_long_simulation(50, 480)
    example_small_ring_graph_long_simulation(50, 490)
    example_small_ring_graph_long_simulation(50, 499)

    example_large_ring_graph_long_simulation(100, 0)
    example_large_ring_graph_long_simulation(100, 10)
    example_large_ring_graph_long_simulation(100, 20)
    example_large_ring_graph_long_simulation(100, 30)
    example_large_ring_graph_long_simulation(100, 40)
    example_large_ring_graph_long_simulation(100, 50)
    example_large_ring_graph_long_simulation(100, 60)
    example_large_ring_graph_long_simulation(100, 70)
    example_large_ring_graph_long_simulation(100, 80)
    example_large_ring_graph_long_simulation(100, 90)
    example_large_ring_graph_long_simulation(100, 100)
    example_large_ring_graph_long_simulation(100, 110)
    example_large_ring_graph_long_simulation(100, 120)
    example_large_ring_graph_long_simulation(100, 130)
    example_large_ring_graph_long_simulation(100, 140)
    example_large_ring_graph_long_simulation(100, 150)
    example_large_ring_graph_long_simulation(100, 160)
    example_large_ring_graph_long_simulation(100, 170)
    example_large_ring_graph_long_simulation(100, 180)
    example_large_ring_graph_long_simulation(100, 190)
    example_large_ring_graph_long_simulation(100, 200)
    example_large_ring_graph_long_simulation(100, 210)
    example_large_ring_graph_long_simulation(100, 220)
    example_large_ring_graph_long_simulation(100, 230)
    example_large_ring_graph_long_simulation(100, 240)
    example_large_ring_graph_long_simulation(100, 250)
    example_large_ring_graph_long_simulation(100, 260)
    example_large_ring_graph_long_simulation(100, 270)
    example_large_ring_graph_long_simulation(100, 280)
    example_large_ring_graph_long_simulation(100, 290)
    example_large_ring_graph_long_simulation(100, 300)
    example_large_ring_graph_long_simulation(100, 310)
    example_large_ring_graph_long_simulation(100, 320)
    example_large_ring_graph_long_simulation(100, 330)
    example_large_ring_graph_long_simulation(100, 340)
    example_large_ring_graph_long_simulation(100, 350)
    example_large_ring_graph_long_simulation(100, 360)
    example_large_ring_graph_long_simulation(100, 370)
    example_large_ring_graph_long_simulation(100, 380)
    example_large_ring_graph_long_simulation(100, 390)
    example_large_ring_graph_long_simulation(100, 400)
    example_large_ring_graph_long_simulation(100, 410)
    example_large_ring_graph_long_simulation(100, 420)
    example_large_ring_graph_long_simulation(100, 430)
    example_large_ring_graph_long_simulation(100, 440)
    example_large_ring_graph_long_simulation(100, 450)
    example_large_ring_graph_long_simulation(100, 460)
    example_large_ring_graph_long_simulation(100, 470)
    example_large_ring_graph_long_simulation(100, 480)
    example_large_ring_graph_long_simulation(100, 490)
    example_large_ring_graph_long_simulation(100, 499)
    
    # example_quite_large_r100g_graph_short_simulation(250, 100)
    # example_quite_large_ring_graph_long_simulation(250, 0)
    # example_quite_large_ring_graph_long_simulation(250, 10)
    # example_quite_large_ring_graph_long_simulation(250, 20)
    # example_quite_large_ring_graph_long_simulation(250, 30)
    # example_quite_large_ring_graph_long_simulation(250, 40)
    # example_quite_large_ring_graph_long_simulation(250, 50)
    # example_quite_large_ring_graph_long_simulation(250, 60)
    # example_quite_large_ring_graph_long_simulation(250, 70)
    # example_quite_large_ring_graph_long_simulation(250, 80)
    # example_quite_large_ring_graph_long_simulation(250, 90)
    # example_quite_large_ring_graph_long_simulation(250, 100)
    # example_quite_large_ring_graph_long_simulation(250, 110)
    # example_quite_large_ring_graph_long_simulation(250, 120)
    # example_quite_large_ring_graph_long_simulation(250, 130)
    # example_quite_large_ring_graph_long_simulation(250, 140)
    # example_quite_large_ring_graph_long_simulation(250, 150)
    # example_quite_large_ring_graph_long_simulation(250, 160)
    # example_quite_large_ring_graph_long_simulation(250, 170)
    # example_quite_large_ring_graph_long_simulation(250, 180)
    # example_quite_large_ring_graph_long_simulation(250, 190)
    # example_quite_large_ring_graph_long_simulation(250, 200)
    # example_quite_large_ring_graph_long_simulation(250, 250)
    # example_quite_large_ring_graph_long_simulation(250, 260)
    # example_quite_large_ring_graph_long_simulation(250, 270)
    # example_quite_large_ring_graph_long_simulation(250, 280)
    # example_quite_large_ring_graph_long_simulation(250, 290)
    # example_quite_large_ring_graph_long_simulation(250, 300)
    # example_quite_large_ring_graph_long_simulation(250, 310)
    # example_quite_large_ring_graph_long_simulation(250, 320)
    # example_quite_large_ring_graph_long_simulation(250, 330)
    # example_quite_large_ring_graph_long_simulation(250, 340)
    # example_quite_large_ring_graph_long_simulation(250, 350)
    # example_quite_large_ring_graph_long_simulation(250, 499)

    # example_very_large_ri250graph_short_simulation(500, -1)
    # example_very_large_ring_graph_long_simulation(500, -1)

    # example_very_large_ring_graph_long_simulation(500, 0)
    # example_very_large_ring_graph_long_simulation(500, 1)
    # example_very_large_ring_graph_long_simulation(500, 5)
    # example_very_large_ring_graph_long_simulation(500, 6)
    # example_very_large_ring_graph_long_simulation(500, 7)
    # example_very_large_ring_graph_long_simulation(500, 8)
    # example_very_large_ring_graph_long_simulation(500, 9)
    # example_very_large_ring_graph_long_simulation(500, 10)
    # example_very_large_ring_graph_long_simulation(500, 25)
    # example_very_large_ring_graph_long_simulation(500, 50)
    # example_very_large_ring_graph_long_simulation(500, 75)
    # example_very_large_ring_graph_long_simulation(500, 99)






