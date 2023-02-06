#include "examples/headers/ds_examples_ring.h"

Eigen::MatrixXd Ring(int n){
    Eigen::MatrixXd Matrix(n, n);
    Matrix.setZero();
    Matrix(0, n-1) = 1; 

    for (size_t i=0;i<n;++i){
        for (size_t j=0;j<n;++j){
            if ((j==i) || (j==(i+1)%n) || ((i!=0) && (j==(i-1)%n))){
                Matrix(i,j) = 1;
            }
        }
    }
    return Matrix;
}


void DiscreteRingGraphSimulation(int n, double a, double b, double tend, double h){

    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;
    unsigned int jump = 1;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_ring_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_ring_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc2, output[0]);
    write_data(file_loc1, output[1]);

}

void DiscreteRandomSimulation(int n, double a0, double b0){

    Eigen::VectorXd W0(n);
    W0.setZero();
    Eigen::VectorXd PHI(n);
    PHI.setRandom();
    PHI = (PHI.array()*M_PI + M_PI).matrix();
    Eigen::MatrixXd K0(n,n);
    K0.setRandom();

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = 100000;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = 10000;
    const double a = a0;
    const double b = b0;
    unsigned int jump = 200;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_random_with_" + std::to_string(n) + "_oscillators.txt";
    std::string file_loc2 = "txt_outputs/discrete_random_with_" + std::to_string(n) + "_oscillators_phases.txt";

    write_data(file_loc1, output[1]);
    write_data(file_loc2, output[0]);
}


void DiscreteCosSimulation(int n, double a, double b, double tend){

    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;
    unsigned int jump = 1;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc2, output[0]);
    write_data(file_loc1, output[1]);

}

std::vector<std::vector<std::vector<Eigen::MatrixXd>>> Comparison(int n, double a, double b){

    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};

    double tend = 40;
    int numsteps = 400;

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    ContSystem.num_steps = numsteps;
    ContSystem.ro = 1;
    ContSystem.epsilon = 0.01;
    ContSystem.t0 = 0;
    ContSystem.t_end = tend;

    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);
    
    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = numsteps;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    unsigned int jump = 1;

    std::vector<std::vector<Eigen::MatrixXd>> contlim_output = ContSystem.run(phi, w, K, a, b, jump);
    std::vector<std::vector<Eigen::MatrixXd>> disc_output = system.run(PHI, a, b, jump);

    std::string file_loc1 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators.txt";
    std::string file_loc2 = "txt_outputs/contlim_cos_with_" + std::to_string(n) + "_oscillators.txt";

    write_data(file_loc1, disc_output[1]);
    write_data(file_loc2, contlim_output[1]);

    std::vector<std::vector<std::vector<Eigen::MatrixXd>>> result;
    result.push_back(contlim_output);
    result.push_back(disc_output);

    return result;

}

void DiscreteErdosReyniSimulation(int n, double a, double b, double tend, double p){


    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = DiscreteErdosReyniGraph(n, p);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;
    unsigned int jump = 1;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_erdos_reyni_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_erdos_reyni_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    write_data(file_loc2, output[0]);
    write_data(file_loc1, output[1]);

}

