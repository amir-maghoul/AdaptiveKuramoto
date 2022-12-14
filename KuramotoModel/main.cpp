#include "include/Headers/adaptive_kuramoto.h"
#include "include/Headers/continuum_limit.h"
#include "include/Headers/runge_kutta.h"
#include "include/Headers/solvers.h"
#include "visualization/visualization.h"
#include "include/Headers/integrators.h"
#include "include/Headers/integral_solver.h"
#include "examples/headers/ds_examples.h"
#include "examples/headers/cl_examples.h"
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

    // std::vector<int> n = {50, 100, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900};
    // std::vector<int> n = {300, 400, 500, 600, 700, 800, 900, 1000, 1100};
    std::vector<int> n = {50, 100, 150, 200, 250, 300};



    // for (size_t i=0; i<n.size();++i){
    //     DiscreteCosSimulation(n.at(i), 0, 0);
    //     ContinuumLimitCosGraphSimulation(n.at(i), 0, 0);
    // }
    for (size_t i=0; i<n.size();++i){
        std::vector<std::vector<std::vector<Eigen::MatrixXd>>> result = Comparison(n.at(i), 0, 0);

        std::vector<std::vector<Eigen::MatrixXd>> ContlimResult = result[0];
        std::vector<std::vector<Eigen::MatrixXd>> DiscreteResult = result[1];

        std::vector<Eigen::MatrixXd> ContlimWeights = ContlimResult[1];
        std::vector<Eigen::MatrixXd> DiscreteWeights = DiscreteResult[1];

        std::cout << "Maximum norm" << std::endl;
        std::cout << (ContlimWeights.at(99) - DiscreteWeights.at(99)).cwiseAbs().maxCoeff() << std::endl;
        std::cout << "Frobenius norm" << std::endl;
        std::cout << (ContlimWeights.at(99) - DiscreteWeights.at(99)).norm() << std::endl;


    };
    // DiscreteCosSimulation(5, 0, 0);



    // ContinuumLimitRandomGraphSimulation(50, 0.3*M_PI, -0.53*M_PI);
    // DiscreteRandomSimulation(100, 0.3*M_PI, -0.53*M_PI);
    // DiscreteRingSimulation(50, -1, -1);
    // DiscreteRingSimulation(100, -1, -1);

    // ContinuumLimitRingGraphSimulation(50, -1, -1);
    // ContinuumLimitRingGraphSimulation(100, -1, -1);

    // DiscreteRingSimulation(250, -1, -1);
    // ContinuumLimitRingGraphSimulation(250, -1, -1);

    // DiscreteRingSimulation(5, 1, -1);
    // ContinuumLimitRingGraphSimulation(5, 1, -1);


    // ContinuumLimitRingGraphSimulation(5, 0.3*M_PI, -0.53*M_PI);
    // ContinuumLimitCosGraphSimulation(5, 0.3*M_PI, -0.53*M_PI);

//     auto w = [](double x){return ZeroFunction(x);};
//     auto K = [](double x, double y){return SinusoidalGraph(x, y);};
//     auto phi = [](double x){return SinFunction(x);};

//     int n = 100;
//     double epsilon = 0.01;

//     ContinuumLimit sys;
//     sys.d = n;
//     sys.num_steps = 500;
//     sys.ro = 1;
//     sys.epsilon = 0.01;
//     sys.t0 = 0;
//     sys.t_end = 20;
//     unsigned int jump = 10;

//     Eigen::VectorXd W0(n);
//     W0.setZero();
//     Eigen::VectorXd PHI0 = sys.DiscretizePhases(phi);
//     Eigen::MatrixXd K0 = sys.DiscretizeWeights(K);

//     Eigen::MatrixXd INTERACTION(n, n);								///< Initializing the interaction matrix between all pairs of Oscillators
// 	INTERACTION << sys.DistanceMatrix(PHI0);								///< Creating the difference matrix	

// 	Eigen::MatrixXd INTERACTION_PHI;								///< Oscillation part of interaction
// 	Eigen::MatrixXd INTERACTION_K;									///< Adaptation part of the interaction
// 	INTERACTION_PHI = (INTERACTION.array()).sin().matrix();		///< Applying the sine function and phase lag
// 	INTERACTION_K 	= (INTERACTION.array()).sin().matrix();		///< Applying the sine function and adaptation lag
	
// 	Eigen::MatrixXd INTEGRAND_PHI;
//     INTEGRAND_PHI = K0.cwiseProduct(INTERACTION_PHI);

// // Creating the derivative equations
// 	Eigen::VectorXd PHI_DOT;										///< Initializing the derivative vector of phases
// 	Eigen::VectorXd PHI_DOT2;
//     Eigen::MatrixXd K_DOT;											///< Initializing the derivative matrix of adjacency coefficients

// 	PHI_DOT2 = W0 - (1.0/n)*(K0.cwiseProduct(INTERACTION_PHI)).rowwise().sum(); ///< Formula: See the method documentation
// 	PHI_DOT = W0 - (IntegralSolvers::TrapMatrixin1D(INTEGRAND_PHI, 0, 1, n, 2, "x"));
//     K_DOT 	= -epsilon*(K0 + INTERACTION_K);							///< Formula

//     // cout << INTEGRAND_PHI << endl;
//     // std::cout << PHI_DOT << std::endl;
//     cout  << "KHAR" << endl;
//     // std::cout << PHI_DOT2 << std::endl;
//     cout  << "GAV" << endl;

//     Eigen::MatrixXd INTERACTION1(n, n);								///< Initializing the interaction matrix between all pairs of Oscillators
// 	INTERACTION1 << sys.DistanceMatrix(PHI_DOT);

//     Eigen::MatrixXd INTERACTION2(n, n);								///< Initializing the interaction matrix between all pairs of Oscillators
// 	INTERACTION2 << sys.DistanceMatrix(PHI_DOT2);
// 	Eigen::MatrixXd INTERACTION_K1;									///< Adaptation part of the interaction
// 	Eigen::MatrixXd INTERACTION_K2;									///< Adaptation part of the interaction

// 	INTERACTION_K1 	= (INTERACTION1.array()).sin().matrix();		///< Applying the sine function and adaptation lag
// 	INTERACTION_K2 	= (INTERACTION2.array()).sin().matrix();		///< Applying the sine function and adaptation lag
//     Eigen::MatrixXd K_DOT1;											///< Initializing the derivative matrix of adjacency coefficients
//     Eigen::MatrixXd K_DOT2;											///< Initializing the derivative matrix of adjacency coefficients
//     K_DOT1 	= -epsilon*(K_DOT + INTERACTION_K1);							///< Formula
//     K_DOT2 	= -epsilon*(K_DOT + INTERACTION_K2);							///< Formula


//     std::cout << (K_DOT2 - K_DOT1).cwiseAbs().maxCoeff() << std::endl;





    // std::string direction = "x";
    // const int n = 100;
    // Eigen::MatrixXd F(n,n);
    // F.setRandom();

    // // std::cout << F << std::endl;

    // Eigen::VectorXd V(4, 1);
    // V <<  1, 2, 3, 4;
    // std::cout << sys.DistanceMatrix(V) << std::endl;

    // cout << "NEWWW" << endl;
    // std::cout << IntegralSolvers::TrapMatrixin1D(INTEGRAND_PHI, 0, 1, n, 2, "x")(0) << std::endl;
    // std::cout << INTEGRAND_PHI.row(0).sum()/n <<std::endl;




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