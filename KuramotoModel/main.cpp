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

auto f = [] (double x, double y)
{
    return x*x + y*y;
};
auto g = [] (double x)
{
    return 1;
};

int main(){

    
    Integrator integral;
    integral.n = 1;

    double result;
    std::vector<double> discrete = integral.DiscretizeSpace();
    
    result = integral.TrapozoidalRule1D(g);
    cout << result << endl;

    cout << "Now 2D........" << endl;
    Eigen::VectorXd V;
    V = integral.TrapozoidalRule1Din2D(f, "x");
    cout << V << endl;

    // LotkaVolterra();
    // TestClustering();
    PlotPhi();
    TestOrderParameter();



    return 0;
}