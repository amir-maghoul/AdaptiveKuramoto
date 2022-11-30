/** This module contains some examples for the discrete adaptive Kuramoto Model**/

#ifndef _EXAMPLES_H_
#define _EXAMPLES_H_

#include "include/Headers/solvers.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/adaptive_kuramoto.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include "iofunctions.h"
#include <iostream>
#include <fstream>
#include <eigen/Dense>

void PlotPhi();
void TestOrderParameter();
void TestClustering();


#endif