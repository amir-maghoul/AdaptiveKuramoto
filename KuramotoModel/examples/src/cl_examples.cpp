/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples.h"
#include <random>


double h = 0.1;
double RandomLow = -1.0;
double RandomHigh = 1.0;

double RandomWeights(double x, double y){
    return RandomGraph(x, y, RandomLow, RandomHigh);
}

double phiRandom(double x){
    return RandomFunction(x, RandomLow, RandomLow);
}

double phiExp(double x){
    return ExpFunction(x);
}
// auto phi = [](double x) {return ExpFunction(x);};
double wZero(double x){
    return ZeroFunction(x);
}
// auto w = [] (double x) {return ZeroFunction(x);};
double KRing(double x, double y){
    return RingLatticeGraph(x, y, h);
}

void SmallRingTopology()
{

    ContinuumLimit system;
    system.d = 10;
    system.num_steps = 1000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10;

    std::cout << system.DiscretizeWeights(RandomWeights) << std::endl;

    // std::cout << system.DiscretizeWeights(K) << std::endl;
    // std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, wZero, KRing);

    // std::string file_loc1 = "txt_outputs/contlim_small_ring_graph.txt";
    // write_data(file_loc1, output[1]);
    // std::cout << output.at(1).at(0).reshaped(d, d) << std::endl;
}

