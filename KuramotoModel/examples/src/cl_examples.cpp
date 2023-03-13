/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples.h"
#include <random>

namespace plt = matplotlibcpp;

void ContinuumLimitRingGraphSimulation(int d, double a, double b, double tend, double h, unsigned int jump){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};
    auto phi = [](double x){return SinFunction(x);};

    ContinuumLimit system;
    system.d = d;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    // std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);
    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, phi, K, a, b, jump);




    std::string file_loc1 = "txt_outputs/contlim_ring_with_" + std::to_string(d) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/contlim_ring_with_" + std::to_string(d) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);

}

void ContinuumLimitCosGraphSimulation(int d, const double a, const double b, double tend, unsigned int jump){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};

    ContinuumLimit system;
    system.d = d;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    // std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);
    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, phi, K, a, b, jump);



    std::string file_loc1 = "txt_outputs/contlim_cos_with_" + std::to_string(d) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/contlim_cos_with_" + std::to_string(d) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);

}

void ContinuumLimitRingGraphSimulationWithGaussInitials(int d, const double a, const double b, unsigned int jump){

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

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_gauss_with_" + std::to_string(d) + "_oscillators.txt";
    write_data(file_loc1, output[1]);

}

void ContinuumLimitRandomGraphSimulation(int d, const double a, const double b, unsigned int jump){

    double h = 0.1;
    double RandomHigh = 1;
    double RandomLow = -1;

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [h, RandomLow, RandomHigh](double x, double y){return RandomGraph(x, y, RandomLow, RandomHigh);};
    auto phi = [RandomLow, RandomHigh](double x){return RandomFunction(x, RandomLow, RandomHigh);};


    ContinuumLimit system;
    system.d = d;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_random_with_" + std::to_string(d) + "_oscillators.txt";
    std::string file_loc2 = "txt_outputs/contlim_random_with_" + std::to_string(d) + "_oscillators_phases.txt";

    write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);
}

void ContinuumLimitErdosReyniGraphSimulation(int d, const double a, const double b, double tend, double p, unsigned int jump){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [p](double x, double y){return ContinuousErdosReyniGraph(x, y, p);};
    auto phi = [](double x){return SinFunction(x);};

    ContinuumLimit system;
    system.d = d;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    // std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);
    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, phi, K, a, b, jump);



    std::string file_loc1 = "txt_outputs/contlim_erdos_reyni_with_" + std::to_string(d) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/contlim_erdos_reyni_with_" + std::to_string(d) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);
    
}