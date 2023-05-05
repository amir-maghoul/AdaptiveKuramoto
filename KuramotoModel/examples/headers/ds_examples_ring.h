#ifndef _DS_EXAMPLES_H_
#define _DS_EXAMPLES_H_

#include "density_functions.h"
#include "discrete_graphs.h"
#include "include/Headers/iofunctions.h"
#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/continuum_limit.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include <eigen/Dense>
#include <iostream>
#include <fstream>
#include <chrono>

Eigen::MatrixXd Ring(int n);

void DiscreteRingGraphSimulation(int n, double a, double b, double tend, double h, unsigned int jump);
void DiscreteRandomSimulation(int n, double a0, double b0, double tend, unsigned int jump);
void DiscreteCosSimulation(int n, double a, double b, double tend, unsigned int jump);
void DiscreteErdosReyniGraphSimulation(int n, double a, double b, double tend, double p, unsigned int jump);
std::vector<std::vector<std::vector<Eigen::MatrixXd>>> Comparison(int n, double a, double b, unsigned int jump);

template<typename F>
void DiscreteExactSimulation(int n, double a, double b, double tend, unsigned int jump, F &&PhiTilde){

    auto w = [](double x){return ZeroFunction(x);};
    // auto phi = [](double x){return SinFunction(x);};
    auto K = [b](double x, double y){return SinusGraph(x, y, b);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    // Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(PhiTilde);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_exact_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_exact_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    WriteData(file_loc2, output[0]);
    WriteData(file_loc1, output[1]);

}

#endif