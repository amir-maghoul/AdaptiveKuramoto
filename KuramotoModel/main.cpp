#include <iostream>
#include <include/abstract_kuramoto.h>
#include <include/adaptive_kuramoto.h>
#include <Eigen/Dense>

using namespace std;


int main(){
    Eigen::Matrix<double, 3, 1> w {28, 19, 11};
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;

    AdaptiveKuramoto empty(w, K0);
    cout << empty.W << endl;
    // Eigen::Matrix a = empty.dynamics();



    return 0;
}