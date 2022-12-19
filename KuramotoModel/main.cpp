#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/continuum_limit.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/solvers.h"
#include "visualization/visualization.h"
#include "include/Headers/integrators.h"
#include "include/Headers/integral_solver.h"
#include "examples/headers/ds_examples.h"
#include "examples/headers/cl_examples_ring.h"
#include "examples/headers/cl_examples_cos.h"
#include "examples/headers/ds_examples_ring.h"
#include <eigen/Dense>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <functional>
#include <chrono>
#include <time.h>

using namespace std;
using namespace Eigen;



int main(){
    time_t my_time = time(NULL);
    cout << ctime(&my_time) << endl;

    omp_set_num_threads(8);
    Eigen::setNbThreads(8);

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
// for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();

    // SmallCosGraphShortSimulation();

    // SmallCosGraphLongSimulation();
    // LargeCosGraphLongSimulation();
    // QuiteLargeCosGraphLongSimulation();

    // DiscreteRingSimulation(50, 0.3*M_PI, -0.53*M_PI);
    // DiscreteRingSimulation(100, 0.3*M_PI, -0.53*M_PI);
    DiscreteRingSimulation(250, 0.3*M_PI, -0.53*M_PI);

    // SmallRingGraphShortSimulation();
    // SmallRingGraphLongSimulation();
    // LargeRingGraphLongSimulation();
    // QuiteLargeRingGraphLongSimulation();
    // VeryLargeRingGraphLongSimulation();
    // VeryLargeRingGraphLongSimulation();
    // VeryLargeCosGraphLongSimulation();


    const sec duration = clock::now() - before;
    std::cout << "Main took " << duration.count() << "s" << std::endl;

    system("/usr/bin/notify-send CodeStatus \"Simulation Ended\"");
    // system("/usr/bin/xmessage -center Simulation Ended");

    // LotkaVolterra();
    // TestClustering();
    // PlotPhi();
    // TestOrderParameter();


    return 0;
};