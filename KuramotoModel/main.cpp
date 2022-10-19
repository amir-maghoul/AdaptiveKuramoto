#include <iostream>
#include "include/abstract_kuramoto.h"
#include "include/adaptive_kuramoto.h"
#include "include/runge_kutta.h"
#include "include/solvers.h"
#include <Eigen/Dense>
#include <vector>
#include <typeinfo>
#include "visualization/visualization.h"
// #include <arrayobject.h>
using namespace std;
using namespace Eigen;


auto f = [] (Eigen::VectorXd y) {
Eigen::VectorXd df(2);
df << y(0)*(4-4.0/3*y(1)) , -y(1)*(0.8-0.4*y(0));
return df;
};


int main(){
    Eigen::Matrix<double, 3, 1> w {M_PI/6, M_PI, M_PI/2};
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;

    int size = w.size();
    Matrix<double, Dynamic, 1> U(size*size + size);
    U << w, K0.reshaped(w.size()*w.size(), 1);
    cout << U << endl;
    Matrix<double, Dynamic, 1> v1(size);
    Matrix<double, Dynamic, 1> v2(size*size);
    v1 << U.head(size);
    v2 << U.tail(size*size);
    cout << "==================" << endl;
    cout << v1 << endl;
    cout << "==================" << endl;
    cout << v2.reshaped(size, size) << endl;

    Matrix<double, Dynamic, Dynamic> M(size,size);
    for (unsigned int i; i<size;++i){
        M.col(i) = w;
    };
    cout << M << endl;
    cout << "))))))))))))))))))))))))))))" << endl;

    Matrix<double, Dynamic, Dynamic> M2(size,size);
    AdaptiveKuramoto empty(w, K0);
    cout << empty.num_steps << endl;
    empty.num_steps = 100;
    cout << empty.num_steps << endl;
    // M = empty.TileRows(w.transpose());
    // M2 = empty.TileCols(w);
    // // M = M2 - M;
    // // M = M.array().sin().matrix();
    // cout << 2*K0 << endl;
    // cout << "=================================="<< endl;
    // Eigen::MatrixXd a = empty.Dynamics(U);
    // std::cout << a << std::endl;

    Eigen::Vector3d X0(M_PI, M_PI/2, M_PI/6);
    // std::vector<Eigen::VectorXd> b = empty.run(X0, 1, 3);
    std::vector<std::vector<Eigen::MatrixXd>> d = empty.run(X0, 1, 2);
    cout << "////////////////////////////////////////" << endl;
    // cout << d[0][1] << endl;



    return 0;
}