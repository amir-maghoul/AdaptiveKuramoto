#include "examples/headers/ds_examples.h"


namespace plt = matplotlibcpp;

struct Data{

    Eigen::Vector3d W;
    Eigen::Matrix3d K0;
    int num_steps;
    double epsilon;
    double ro;
    double t_end;
    int jump ;
    const unsigned int m = 2;
    Eigen::Vector3d X0;

    void setData(){
        W = {28, 19, 11};
        // W = {M_PI/2, M_PI/4, M_PI/6};
        // W = {0.2, 0.1, 0.3};
        // W.setZero();

        // K0.setOnes();
        // K0.setZero();
        K0 <<  0,   0.2,  1.1,
               0.5, 0,   -0.7,
               0.3, 0.9,  0;

        num_steps = 1000;
        epsilon = 0.01;
        ro = 1;
        t_end = 40;
        jump = 2;
        X0 = {0, M_PI, 0};
};};

void PlotPhi(){

    Data data;
    data.setData();

    AdaptiveKuramoto obj(data.W, data.K0);
    obj.num_steps = data.num_steps;
    obj.epsilon = data.epsilon;
    obj.ro = data.ro;
    obj.t_end = data.t_end;
    int jump = data.jump;

    Eigen::Vector3d X0(0, M_PI, 0);
    std::vector<std::vector<Eigen::MatrixXd>> output = obj.run(X0, 0, 0, jump);

    int real_steps = (int) obj.num_steps/(jump-1);
    std::vector<double> t(real_steps);
    std::vector<double> u0(real_steps);
    std::vector<double> u1(real_steps);
    std::vector<double> u2(real_steps);
    std::vector<Eigen::Vector3d> PHI_DOT(real_steps);
    double h = (obj.t_end - obj.t0)/(double) real_steps;
    
    for(size_t i = 0; i < t.size(); i++) {
        t[i] = i*h;
        PHI_DOT[i] = (output[0][i+1] - output[0][i])*(1.0/h);
    };

    for(size_t i = 0; i < t.size(); i++) {
        u0[i] = PHI_DOT[i](0);
        u1[i] = PHI_DOT[i](1);
        u2[i] = PHI_DOT[i](2);
    };


    plt::figure();
    plt::title("Adaptive Kuramoto Model Phases");
    plt::named_plot("Phase Velocity",t, u1);
    plt::xlabel("Time");
    plt::ylabel("Phase Velocity");
    plt::legend();
    plt::save("Frequencies.png");
};

void TestOrderParameter()
{
    Data data;
    data.setData();

    AdaptiveKuramoto obj(data.W, data.K0);
    obj.num_steps = data.num_steps;
    obj.epsilon = data.epsilon;
    obj.ro = data.ro;
    obj.t_end = data.t_end;
    int jump = data.jump;
    const unsigned int m = data.m;

    Eigen::Vector3d X0 = data.X0;
    std::vector<std::vector<Eigen::MatrixXd>> output = obj.run(X0, 0, 0, jump);

    std::vector<double> R(2);
    std::vector<double> order_parameter; 

    for (size_t i=0;i<output[0].size();++i)
    {
        R = obj.OrderParameter(output[0][i], m);
        order_parameter.push_back(R.at(0));
    };
    std::string file_loc2 = "txt_outputs/phases_file.txt";
    write_data(file_loc2, output[0]);
    std::string file_loc = "txt_outputs/order_parameter_file.txt";
    // write_vector(file_loc, order_parameter);
};

void TestClustering()
{   
    const int n = 50;
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
    obj.t_end = 50000;
    obj.epsilon = 0.01;
    obj.ro = 1;
    unsigned int jump = 1000;

    std::vector<std::vector<Eigen::MatrixXd>> output = obj.run(U0, 0.3*M_PI, 0.53*M_PI, jump);

    std::string file_loc1 = "txt_outputs/clustering_file.txt";
    write_data(file_loc1, output[1]);
    std::string file_loc2 = "txt_outputs/phases_file.txt";
    write_data(file_loc2, output[0]);

};