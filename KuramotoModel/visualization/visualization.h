#ifndef _VISUALIZATION_H_
#define _VISUALIZATION_H_

#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/solvers.h"
#include "include/Headers/runge_kutta.h"
#include <Matplotlib/matplotlibcpp.h>
#include <Eigen/Dense>
#include <iostream> 

namespace plt = matplotlibcpp;

void adaptiveKuramoto();
void LotkaVolterra();
void LorenzAttractor();


#endif
