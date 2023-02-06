/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#ifndef _CL_EXAMPLES_H_
#define _CL_EXAMPLES_H_

#include "density_functions.h"
#include "discrete_graphs.h"
#include "iofunctions.h"
#include "include/Headers/continuum_limit.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include <eigen/Dense>
#include <iostream>
#include <fstream>
#include <chrono>

void ContinuumLimitRingGraphSimulation(int n, const double a, const double b, double tend, double h);
void ContinuumLimitCosGraphSimulation(int d, const double a, const double b, double tend);
void ContinuumLimitRingGraphSimulationWithGaussInitials(int d, const double a, const double b);
void ContinuumLimitRandomGraphSimulation(int d, const double a, const double b);
void ContinuumLimitErdosReyniGraphSimulation(int d, const double a, const double b, double tend, double p);


#endif