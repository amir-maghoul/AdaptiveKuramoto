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

void SmallRingGraphLongSimulation(){

    double h = 0.01;
    double RandomLow = -1.0;
    double RandomHigh = 1.0;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 50;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_small_ring_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}

void LargeRingGraphLongSimulation(){

    double h = 0.01;
    double RandomLow = -1.0;
    double RandomHigh = 1.0;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 100;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_large_ring_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}

void QuiteLargeRingGraphLongSimulation(){

    double h = 0.01;
    double RandomLow = -1.0;
    double RandomHigh = 1.0;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 250;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_quite_large_ring_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}

void VeryLargeRingGraphLongSimulation(){

    double h = 0.1;
    double RandomLow = -1.0;
    double RandomHigh = 1.0;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 500;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 50000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 500;

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
// for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    const sec duration = clock::now() - before;
    std::cout << "It took " << duration.count() << "s" << std::endl;

    std::string file_loc1 = "txt_outputs/contlim_very_large_ring_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}