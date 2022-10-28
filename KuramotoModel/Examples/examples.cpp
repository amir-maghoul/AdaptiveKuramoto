#include "Examples/examples.h"
using namespace std;

namespace plt = matplotlibcpp;

void RandomMatrix()
{   
    const int n = 4;
    typedef Eigen::Matrix<double, n, 1> Vector100d;
    typedef Eigen::Matrix<double, n, n> Matrix100d;
    Vector100d w0;
    Vector100d u0;
    Matrix100d K0;

    u0 = Vector100d::Random();
    w0 = Vector100d::Zero();
    K0 = Matrix100d::Random();

    AdaptiveKuramoto obj(w0, K0);
    obj.num_steps = 1000;
    obj.epsilon = 0.01;
    obj.ro = 1;
    cout << w0 << endl;

};