/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#ifndef _CL_EXAMPLES_COS_H_
#define _CL_EXAMPLES_COS_H_

#include "density_functions.h"
#include "iofunctions.h"
#include "include/Headers/continuum_limit.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include <eigen/Dense>
#include <iostream>
#include <fstream>
#include <chrono>

void SmallCosGraphShortSimulation();
void SmallCosGraphLongSimulation();

void LargeCosGraphShortSimulation();
void LargeCosGraphLongSimulation();

void QuiteLargeCosGraphShortSimulation();
void QuiteLargeCosGraphLongSimulation();

void VeryLargeCosGraphShortSimulation();
void VeryLargeCosGraphLongSimulation();


#endif