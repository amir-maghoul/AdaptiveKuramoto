#ifndef _DS_EXAMPLES_H_
#define _DS_EXAMPLES_H_

#include "density_functions.h"
#include "discrete_graphs.h"
#include "iofunctions.h"
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
void DiscreteErdosReyniSimulation(int n, double a, double b, double tend, double p, unsigned int jump);
std::vector<std::vector<std::vector<Eigen::MatrixXd>>> Comparison(int n, double a, double b, unsigned int jump);

#endif