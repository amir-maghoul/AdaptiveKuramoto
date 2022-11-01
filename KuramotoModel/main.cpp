#include "include/Headers/abstract_kuramoto.h"
#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/solvers.h"
#include "visualization/visualization.h"
#include "examples/examples.h"
#include <eigen/Dense>
#include <vector>
#include <typeinfo>
#include <iostream>

using namespace std;
using namespace Eigen;



int main(){


    // LotkaVolterra();
    // TestClustering();
    PlotPhi();
    TestOrderParameter();



    return 0;
}