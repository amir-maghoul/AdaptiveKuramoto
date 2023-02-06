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

void DiscreteRingGraphSimulation(int n, double a, double b, double tend, double h);
void DiscreteRandomSimulation(int n, double a0, double b0, double tend);
void DiscreteCosSimulation(int n, double a, double b, double tend);
void DiscreteErdosReyniSimulation(int n, double a, double b, double tend, double p);
std::vector<std::vector<std::vector<Eigen::MatrixXd>>> Comparison(int n, double a, double b);

#endif