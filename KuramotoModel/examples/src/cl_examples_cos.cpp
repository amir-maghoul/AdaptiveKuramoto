/** This module contains some examples for the continuum limit of adaptive Kuramoto Model**/

#include "examples/headers/cl_examples_cos.h"
#include <random>

namespace plt = matplotlibcpp;


void SmallCosGraphLongSimulation(){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 50;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_small_cos_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}


void LargeCosGraphLongSimulation(){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 100;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_large_cos_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}


void QuiteLargeCosGraphLongSimulation(){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 250;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 500;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    std::string file_loc1 = "txt_outputs/contlim_quite_large_cos_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}

void VeryLargeCosGraphShortSimulation(){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 500;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 1000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 500;

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
// for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    const sec duration = clock::now() - before;
    std::cout << "It took " << duration.count() << "s" << std::endl;

    std::string file_loc1 = "txt_outputs/contlim_very_large_cos_graph_short_simulation.txt";
    write_data(file_loc1, output[1]);
}

void VeryLargeCosGraphLongSimulation(){

    auto w = [](double x){return ZeroFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};
    auto phi = [](double x){return SinFunction(x);};


    ContinuumLimit system;
    system.d = 500;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 5000;
    const double a = 0;
    const double b = 0;
    unsigned int jump = 500;

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
// for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(phi, w, K, a, b, jump);

    const sec duration = clock::now() - before;
    std::cout << "It took " << duration.count() << "s" << std::endl;

    std::string file_loc1 = "txt_outputs/contlim_very_large_cos_graph_long_simulation.txt";
    write_data(file_loc1, output[1]);
}