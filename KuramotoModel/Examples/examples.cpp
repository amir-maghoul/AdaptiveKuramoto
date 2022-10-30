#include "Examples/examples.h"
using namespace std;
using namespace Eigen;

namespace plt = matplotlibcpp;

void write_data(string file_name, vector<MatrixXd> matrix)
{
    cout << "Writing matrix..."<< endl;
    fstream file;
    file.open(file_name, ios_base::out);

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j=0; j < matrix.at(i).size(); ++j)
        {
            file << (matrix.at(i))(j) << ",";    
        }
        file << "\n";
    } 
    file.close();
}

void write_vector(string file_name, vector<double> vector)
{
    cout << "Writing matrix..."<< endl;
    fstream file;
    file.open(file_name, ios_base::out);

    for (size_t i = 0; i < vector.size(); ++i)
    {
        file << vector.at(i) << ",";    
        file << "\n";
    } 
    file.close();
}

void TestOrderParameter()
{
    Eigen::Vector3d w {28, 19, 11};
    Eigen::Matrix3d K0;
    K0 <<  0,   0.2,  1.1,
           0.5, 0,   -0.7,
           0.3, 0.9,  0;
    
    AdaptiveKuramoto obj(w, K0);
    obj.num_steps = 1000;
    obj.epsilon = 0.01;
    obj.ro = 1;
    obj.t_end = 40;
    int jump = 2;
    const unsigned int m = 1;

    Eigen::Vector3d X0(0, M_PI, 0);
    std::vector<std::vector<Eigen::MatrixXd>> output = obj.run(X0, 0, 0, jump);

    std::vector<double> R;
    std::vector<double> order_parameter;

    for (size_t i;i<output[0].size();++i)
    {
        R = obj.OrderParameter(output[0][i], m);
        order_parameter.push_back(R.at(0));
    };
    string file_loc = "txt_outputs/order_parameter_file.txt";
    write_vector(file_loc, order_parameter);
};

void TestClustering()
{   
    const int n = 100;
    typedef Eigen::Matrix<double, n, 1> Vector100f;
    typedef Eigen::Matrix<double, n, n> Matrix100f;
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

    vector<vector<MatrixXd>> output = obj.run(U0, 0.3*M_PI, 0.53*M_PI, jump);

    string file_loc = "txt_outputs/clustering_file.txt";
    write_data(file_loc, output[1]);

};