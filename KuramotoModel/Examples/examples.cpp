#include "Examples/examples.h"
using namespace std;

void RandomMatrix()
{
    typedef Eigen::Matrix<double, 4, 1> Vector100d;
    typedef Eigen::Matrix<double, 100, 100> Matrix100d;
    Vector100d w0;
    w0 = Vector100d::Random();
    cout << w0 << endl;
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;  
};