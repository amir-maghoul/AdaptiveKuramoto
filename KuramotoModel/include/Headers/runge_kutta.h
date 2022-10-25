/**
 * Runge Kutta implementation for arbitrary dimensions.
 * This is a modified version (and slightly optimized) of the implementation in:
 * https://github.com/davidrzs/Runge-Kutta-ODE-Solver
*/

#ifndef _RUNGE_KUTTA_H_
#define _RUNGE_KUTTA_H_

#include <Eigen/Dense>
#include <iostream>
#include <vector>


// template <class StepSolution> 
struct ExplicitRungeKutta {

    const Eigen::MatrixXd B;            ///< The Butcher Tableau of the coefficients
    const Eigen::VectorXd C;            ///< The weight vector in corresponding to elements of Butcher Tableau
    const unsigned int num_steps;       ///< Number of steps in the integration
    const double t0;                    ///< Initial time
    const double tend;                  ///< End time
    const double dt;                    ///< Timestep


/*
***************************************************************
 * Empty constructor, constructor overloading and deconstructor
***************************************************************
*/
    ExplicitRungeKutta();
    ExplicitRungeKutta(const Eigen::MatrixXd &B_IN, const Eigen::VectorXd &C_IN, unsigned int num_steps_in=100, double t0=0, double tend=10) 
            : B{B_IN}, C{C_IN}, t0{t0}, tend{tend},num_steps{num_steps_in}, dt{(tend-t0)/num_steps}{};
    ~ExplicitRungeKutta(){};

/*
****************************************************************
 * Methods
****************************************************************
*/  

    /**
     * Calculates the main Runge Kutta summand using the Butcher Tableau, i.e. sum(h*c_i*k_i) where
     * c_i are the weights and k_i are the main Runge Kutta coefficients
     * 
     * @param f     the right hand side function of the ODE.
     * @param X0    the initial value of the ODE.
     * @param dt    the timestep
     * 
     * @return      One time step of Runge Kutta algorithm.
    */
    template<typename Function>
    // StepSolution CalculateRKSummand(Function &&f, const StepSolution &X0, const double dt)
    Eigen::VectorXd CalculateRKSummand(Function &&f, const Eigen::VectorXd &X0)
    {
        Eigen::VectorXd X1 = X0;                            ///< Current state as previous state in the iteration
        std::vector<Eigen::VectorXd> K;                     ///< Vector of m-th Runge Kutta slope k.

        unsigned int order = B.cols();                      ///< Specifying the mth order of Runge Kutta

        // calculating Runge Kutta summand 
        for(unsigned int m = 0; m < order; m++){
            
            Eigen::VectorXd steps = X0;                     ///< Initialization of the summands
            
            // Loop to calculate the m-th slope
            for(unsigned int j = 0; j < m; j++) steps += dt*B(m,j)*K[j];

            K.push_back(f(steps));                          ///< Save the m-th slope
        }
        // Summing the product of slopes with their corresponding Butcher weight
        for(unsigned int i = 0; i < order; i++){
            X1 += dt*C[i]*K[i];
        }
        return X1;

    };

    /**
     * The Runge Kutta solver. Uses CalculateRKSummand to solve the ODE at different time steps
     *
     * @param f     the right hand side function of the ODE.
     * @param X0    the initial value of the ODE.
     * 
     * @return      std::vector of Eigen::VectorXd of integrated ODE solution.
    */
    template<typename Function>
    std::vector<Eigen::VectorXd> solve(Function &&f, const Eigen::VectorXd &X0)
    {
        std::vector<Eigen::VectorXd> Solutions;             ///< Create empty the solution vector
        Solutions.push_back(X0);                            ///< Start by initial conditions

        // Loop over time steps to create solution at each new timestep
        for(unsigned int i = 0; i < num_steps; i++){

            Solutions.push_back(CalculateRKSummand(f,Solutions.back()));
        }
        return Solutions;
    };

};

#endif