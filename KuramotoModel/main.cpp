#include <iostream>
#include <include/abstract_kuramoto.h>
#include <include/adaptive_kuramoto.h>
#include <include/solvers.h>
#include <Eigen/Dense>
#include <vector>
using namespace std;
using namespace Eigen;


auto f = [] (Eigen::VectorXd y) {
Eigen::VectorXd df(2);
df << y(0)*(4-4.0/3*y(1)) , -y(1)*(0.8-0.4*y(0));

return df;
};

Eigen::VectorXd y0 {6, 3};

int main(){
    Eigen::Matrix<double, 3, 1> w {1, 1, 1};
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;

    AdaptiveKuramoto empty(w, K0);
    cout << empty.W << endl;
    Eigen::MatrixXd a = empty.dynamics();
    std::cout << a.cols() << std::endl;

    Eigen::MatrixXd v1 {{1, 2}, 
                        {3, 4}};
    Eigen::MatrixXd v2 {{5, 7}, 
                        {6, 8}};
    Eigen::MatrixXd v3 = v1.reshaped(v1.size(), 1);

    cout << v3 << endl;
    cout << v3.reshaped(v1.rows(), v1.cols()) << endl;

    cout << K0*w << endl;

    ExplicitRungeKutta RK(K0, w);
    cout << RK.dt << endl;

    Eigen::VectorXd X0 {6, 3};
    std::vector<Eigen::VectorXd> X;
    X = RK.solve(f, X0);
    



    return 0;
}