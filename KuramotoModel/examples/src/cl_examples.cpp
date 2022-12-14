/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples.h"
#include <random>

namespace plt = matplotlibcpp;

void ContinuumLimitRingGraphSimulation(int d, const double a, const double b){

    double h = 0.1;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = d;
    system.num_steps = 10000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 1000;
    unsigned int jump = 20;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_ring_with_" + std::to_string(d) + "_oscillators.txt";
    std::string file_loc2 = "txt_outputs/contlim_ring_with_" + std::to_string(d) + "_oscillators_phases.txt";

    // write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);
}

void ContinuumLimitCosGraphSimulation(int d, const double a, const double b){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = d;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_cos_with_" + std::to_string(d) + "_oscillators.txt";
    write_data(file_loc1, output[1]);
}

void ContinuumLimitRingGraphSimulationWithGaussInitials(int d, const double a, const double b){

    double h = 0.1;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return NormalDistributionFunction(x);};

    ContinuumLimit system;
    system.d = d;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_gauss_with_" + std::to_string(d) + "_oscillators.txt";
    write_data(file_loc1, output[1]);

}