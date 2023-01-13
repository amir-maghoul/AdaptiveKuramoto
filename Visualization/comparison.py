from examples_continuum import *
from examples_discrete import *
from scipy.integrate import trapz
import numpy.linalg as LA


if __name__ == "__main__":
    # np.set_printoptions(precision=8)


    # step = 400
    t = 1
    # n = [50, 100, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900]
    # n = [300, 400, 500, 600, 700, 800, 900, 1000, 1100]
    n = [50, 100, 150, 200, 250]
    # n = [20, 25, 50]
    # n = [7]



    # steps = np.arange(0, step, 10)

    error_matrix = np.zeros((len(n)))
    # error = np.zeros((len(n), step))
    error3 = np.zeros(len(n))
    error4 = np.zeros(len(n))


    for i, n_ in enumerate(n):
        print(f"n = {n_}" )
        # file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/tend_40/contlim_cos_with_{n_}_oscillators.txt"
        file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/contlim_cos_with_{n_}_oscillators.txt"
        cont_matrix = read_matrix_to_array(file_loc, n_)

        print("contlim data read")
        # print("contlim min: ")
        # print(np.amin(cont_matrix))
        # plot_matrix(cont_matrix, t)

        # file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/ComparisonCos/tend_40/discrete_cos_with_{n_}_oscillators.txt"
        file_loc = f"/home/amir/AdaptiveKuramoto/KuramotoModel/txt_outputs/discrete_cos_with_{n_}_oscillators.txt"
        disc_matrix = read_matrix_to_array(file_loc, n_)

        print("discrete data read")
        # print("discrete min: ")
        # print(np.amin(disc_matrix))
        # plot_matrix(disc_matrix, t)


        # error[i, :] = LA.norm(cont_matrix - disc_matrix, axis=(1,2)).T
        error_matrix[i] = np.amax(trapz(np.absolute(cont_matrix[t, :, :] - disc_matrix[t, :, :]), axis=1)/n_)
        error3[i] = LA.norm(cont_matrix[t, :, :] - disc_matrix[t, :, :], "fro")
        error4[i] = np.amax(np.absolute(cont_matrix[t, :, :] - disc_matrix[t, :, :]))




    # # plt.figure()
    # # plt.plot(n, error[:, t])
    plt.figure()
    plt.plot(n, error_matrix)
    plt.figure()
    plt.plot(n, error3)
    plt.title("Frobenius Norm")
    plt.figure()
    plt.plot(n, error4)
    plt.title("Maximum Norm")
    plt.show()

