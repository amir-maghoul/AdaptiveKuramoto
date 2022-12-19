#ifndef _DS_EXAMPLES_H_
#define _DS_EXAMPLES_H_

#include "density_functions.h"
#include "iofunctions.h"
#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/continuum_limit.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include <eigen/Dense>
#include <iostream>
#include <fstream>
#include <chrono>

Eigen::MatrixXd Ring(int n);

void DiscreteRingSimulation(int n, double a0, double b0);

#endif