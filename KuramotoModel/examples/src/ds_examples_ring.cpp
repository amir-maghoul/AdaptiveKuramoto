#include "examples/headers/ds_examples_ring.h"


void DiscreteRingGraphSimulation(int n, double a, double b, double tend, double h, unsigned int jump){

    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};
    auto K = [h](double x, double y){return RingLatticeGraph(x, y, h);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    // Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(phi);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_ring_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_ring_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    WriteData(file_loc2, output[0]);
    WriteData(file_loc1, output[1]);

}

void DiscreteRandomSimulation(int n, double a0, double b0, double tend, unsigned int jump){

    Eigen::VectorXd W0(n);
    W0.setZero();
    Eigen::VectorXd PHI(n);
    PHI.setRandom();
    PHI = (PHI.array()*M_PI + M_PI).matrix();
    Eigen::MatrixXd K0(n,n);
    K0.setRandom();

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;
    const double a = a0;
    const double b = b0;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_random_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) +  ".txt";
    std::string file_loc2 = "txt_outputs/discrete_random_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    WriteData(file_loc1, output[1]);
    WriteData(file_loc2, output[0]);
}


void DiscreteCosSimulation(int n, double a, double b, double tend, unsigned int jump){

    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};
    auto K = [](double x, double y){return SinusoidalGraph(x, y);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    // Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(phi);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    WriteData(file_loc2, output[0]);
    WriteData(file_loc1, output[1]);

}

std::vector<std::vector<std::vector<Eigen::MatrixXd>>> Comparison(int n, double a, double b, unsigned int jump){

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
    // Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = ContSystem.DiscretizeWeights(K);
    
    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = numsteps;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    std::vector<std::vector<Eigen::MatrixXd>> contlim_output = ContSystem.run(phi, w, K, a, b, jump);
    std::vector<std::vector<Eigen::MatrixXd>> disc_output = system.run(PHI, a, b, jump);

    std::string file_loc1 = "txt_outputs/discrete_cos_with_" + std::to_string(n) + "_oscillators.txt";
    std::string file_loc2 = "txt_outputs/contlim_cos_with_" + std::to_string(n) + "_oscillators.txt";

    WriteData(file_loc1, disc_output[1]);
    WriteData(file_loc2, contlim_output[1]);

    std::vector<std::vector<std::vector<Eigen::MatrixXd>>> result;
    result.push_back(contlim_output);
    result.push_back(disc_output);

    return result;

}

void DiscreteErdosReyniGraphSimulation(int n, double a, double b, double tend, double p, unsigned int jump){


    auto w = [](double x){return ZeroFunction(x);};
    auto phi = [](double x){return SinFunction(x);};

    ContinuumLimit ContSystem;
    ContSystem.d = n;
    // Eigen::VectorXd W0 = ContSystem.DiscretizePhases(w);
    Eigen::VectorXd W0 = ContSystem.DiscretizePhases(phi);
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    Eigen::MatrixXd K0 = DiscreteErdosReyniGraph(n, p);

    AdaptiveKuramoto system(W0, K0);
    system.n = n;
    system.num_steps = (int) tend*10;
    system.ro = 1;
    system.epsilon = 0.01;
    system.t0 = 0;
    system.t_end = tend;

    std::vector<std::vector<Eigen::MatrixXd>> output = system.run(PHI, a, b, jump);
    std::string file_loc1 = "txt_outputs/discrete_erdos_reyni_with_" + std::to_string(n) + "_oscillators_tend_" + std::to_string((int) system.t_end) + ".txt";
    std::string file_loc2 = "txt_outputs/discrete_erdos_reyni_with_" + std::to_string(n) + "_oscillators_phases_tend_" + std::to_string((int) system.t_end) + ".txt";

    WriteData(file_loc2, output[0]);
    WriteData(file_loc1, output[1]);

}

