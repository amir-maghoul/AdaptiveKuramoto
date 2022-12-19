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


void DiscreteRingSimulation(int n, double a0, double b0){
    auto phi = [](double x){return SinFunction(x);};
    ContinuumLimit ContSystem;
    ContSystem.d = n;

    Eigen::VectorXd W0(n);
    W0.setZero();
    Eigen::VectorXd PHI = ContSystem.DiscretizePhases(phi);
    // PHI.setRandom();
    Eigen::MatrixXd K0 = Ring(n);

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
    std::string file_loc1 = "txt_outputs/discrete_ring_with_" + std::to_string(n) + "_oscillators.txt";
    write_data(file_loc1, output[1]);

}

