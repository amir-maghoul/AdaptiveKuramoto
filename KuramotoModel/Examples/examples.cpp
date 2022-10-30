#include "Examples/examples.h"
using namespace std;
using namespace Eigen;

namespace plt = matplotlibcpp;

void write_data(string file_name, vector<MatrixXf> matrix, size_t jump)
{
    cout << "Writing data..."<< endl;
    fstream file;
    file.open(file_name, ios_base::out);

    for (size_t i = 0; i < matrix.size(); i+=jump)
    {
        for (size_t j=0; j < matrix.at(i).size(); ++j)
        {
            file << (matrix.at(i))(j) << ",";    
        }
        file << "\n";
    } 
    file.close();
}

void RandomMatrix()
{   
    const int n = 100;
    typedef Eigen::Matrix<float, n, 1> Vector100f;
    typedef Eigen::Matrix<float, n, n> Matrix100f;
    Vector100f W0;
    Vector100f U0;
    Matrix100f K0;

    U0 = Vector100f::Random();
    W0 = Vector100f::Zero();
    K0 = Matrix100f::Random();

    AdaptiveKuramoto obj(W0, K0);
    obj.num_steps = 100000;
    obj.t_end = 10000;
    obj.epsilon = 0.01;
    obj.ro = 1;
    unsigned int jump = 1000;

    vector<vector<MatrixXf>> output = obj.run(U0, 0.3*M_PI, 0.53*M_PI, jump);

    string file_loc = "txt_outputs/vector_file.txt";
    write_data(file_loc, output[1], 100);

};