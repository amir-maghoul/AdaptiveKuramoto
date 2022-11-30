/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples.h"


double h = 0.1;

double phi(double x){
    return ExpFunction(x);
}
// auto phi = [](double x) {return ExpFunction(x);};
double w(double x){
    return ZeroFunction(x);
}
// auto w = [] (double x) {return ZeroFunction(x);};
double K(double x, double y){
    return RingLatticeGraph(x, y, h);
}

void Test()
{
    // auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};

    ContinuumLimit system;
    system.d = 50;

    std::cout << system.DiscretizeWeights(K) << std::endl;
    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K);

    std::string file_loc1 = "txt_outputs/contlim_clustering_file.txt";
    write_data(file_loc1, output[1]);
    // std::cout << output.at(1).at(0).reshaped(d, d) << std::endl;
}

