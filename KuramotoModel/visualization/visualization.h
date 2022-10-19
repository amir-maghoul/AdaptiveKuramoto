#ifndef _VISUALIZATION_H_
#define _VISUALIZATION_H_

#include "include/solvers.h"
#include "include/runge_kutta.h"
#include "matplotlibcpp.h"
#include <iostream> 

namespace plt = matplotlibcpp;

void adaptiveKuramoto();
void LotkaVolterra();
void LorenzAttractor();


#endif
