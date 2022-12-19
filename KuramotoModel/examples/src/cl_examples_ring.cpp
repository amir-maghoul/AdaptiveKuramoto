/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples_ring.h"
#include <random>

namespace plt = matplotlibcpp;

double h = 0.1;

double phiExp(double x){
    return ExpFunction(x);
}
// auto phi = [](double x) {return ExpFunction(x);};
double wZero(double x){
    return ZeroFunction(x);
}
// auto w = [] (double x) {return ZeroFunction(x);};
double KRing(double x, double y){
    return RingLatticeGraph(x, y, h);
}

void ContinuumLimitRingGraphSimulation(int d, const double a, const double b){

    double h = 0.1;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = d;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    // const double a = 0;
    // const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    // std::string file_loc1 = "txt_outputs/contlim_small_ring_graph_long_simulation.txt";
    std::string file_loc1 = "txt_outputs/contlim_ring_with_" + std::to_string(d) + "_oscillators.txt";
    write_data(file_loc1, output[1]);
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
    // const double a = 0;
    // const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_cos_with_" + std::to_string(d) + "_oscillators.txt";
    write_data(file_loc1, output[1]);
}