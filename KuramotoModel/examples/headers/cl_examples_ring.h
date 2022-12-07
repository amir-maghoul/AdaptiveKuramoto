/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#ifndef _CL_EXAMPLES_H_
#define _CL_EXAMPLES_H_

#include "density_functions.h"
#include "iofunctions.h"
#include "include/Headers/continuum_limit.h"
#include <matplotlibcpp/matplotlibcpp.h>
#include <eigen/Dense>
#include <iostream>
#include <fstream>
#include <chrono>

void SmallRingGraphShortSimulation();
void SmallRingGraphLongSimulation();

void LargeRingGraphShortSimulation();
void LargeRingGraphLongSimulation();

void QuiteLargeRingGraphShortSimulation();
void QuiteLargeRingGraphLongSimulation();

void VeryLargeRingGraphShortSimulation();
void VeryLargeRingGraphLongSimulation();


#endif