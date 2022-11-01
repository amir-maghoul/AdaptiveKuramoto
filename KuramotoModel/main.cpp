#include "include/Headers/abstract_kuramoto.h"
#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/solvers.h"
#include "visualization/visualization.h"
#include "include/Headers/integrators.h"
#include "examples/examples.h"
#include <eigen/Dense>
#include <vector>
#include <typeinfo>
#include <iostream>

using namespace std;
using namespace Eigen;

double function(double x, double y)
{
    return 1;
};

int main(){

    
    Integrator integral;
    integral.F = function;
    integral.n = 2;

    integral.TrapozoidalRule1Din2D();

    // LotkaVolterra();
    // TestClustering();
    PlotPhi();
    TestOrderParameter();



    return 0;
}