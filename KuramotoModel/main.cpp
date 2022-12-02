#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/continuum_limit.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/solvers.h"
#include "visualization/visualization.h"
#include "include/Headers/integrators.h"
#include "include/Headers/integral_solver.h"
#include "examples/headers/ds_examples.h"
#include "examples/headers/cl_examples.h"
#include <eigen/Dense>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <functional>
#include <chrono>

using namespace std;
using namespace Eigen;



int main(){
    omp_set_num_threads(8);
    Eigen::setNbThreads(8);

    // VeryLargeRingGraphLongSimulationShort();
    QuiteLargeRingGraphLongSimulationShort();
    // LargeRingGraphLongSimulationShort();
    // RandomGraphSimulation();
    // SmallRingGraphLongSimulation2();
    // SmallRingGraphLongSimulation();
    // SmallRingTopology();
    // SaveMatrix();

    // double result = IntegralSolvers::Trap1D(g, 0, 1, 100, 1);
    // cout << result << endl;

    // Integrator integral;
    // integral.n = 1;

    // double result;
    // std::vector<double> discrete = integral.DiscretizeSpace();
    
    // result = integral.TrapozoidalRule1D(g);
    // cout << result << endl;

    // cout << "Now 2D........" << endl;
    // Eigen::VectorXd V;
    // V = integral.TrapozoidalRule1Din2D(f, "x");
    // cout << V << endl;

    // Eigen::VectorXd W(5);
    // W << 1, 2, 3, 4, 5;
    // cout << W << endl;
    // cout << "----------------" << endl;

    // Eigen::VectorXd U(4);
    // U = W.segment(1, W.size()-1) + W.segment(0, W.size()-1);

    // cout << U << endl;
    // const int n = 5;
    // typedef Eigen::Matrix<double, n, n> Matrix5f;
    // Eigen::MatrixXd W;
    // W = Matrix5f::Random();

    // Eigen::VectorXd res = IntegralSolvers::TrapMatrixin1D(W, 0, 1, 50, 2, "x");

    // cout << W << endl;
    // cout << res << endl;


    // LotkaVolterra();
    // TestClustering();
    // PlotPhi();
    // TestOrderParameter();


    return 0;
};