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
    Eigen::Matrix<double, 3, 1> w {M_PI/6, M_PI, M_PI/2};
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;

    int size = w.size();

    AdaptiveKuramoto empty(w, K0);


    // Eigen::Vector3d X0(0, M_PI, 0);
    // std::vector<std::vector<Eigen::MatrixXd>> d = empty.run(X0, 1, 2);


    // LotkaVolterra();
    adaptiveKuramoto();
    // TestClustering();
    // TestOrderParameter();



    return 0;
}