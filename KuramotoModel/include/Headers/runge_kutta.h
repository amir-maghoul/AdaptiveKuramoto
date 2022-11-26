/**
 * Runge Kutta implementation for arbitrary dimensions.
 * This is a modified version (and slightly optimized) of the implementation in:
 * https://github.com/davidrzs/Runge-Kutta-ODE-Solver
*/

#ifndef _RUNGE_KUTTA_H_
#define _RUNGE_KUTTA_H_

#include <eigen/Dense>
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
    Eigen::VectorXd CalculateRKSummand(Function &&f, const Eigen::VectorXd &X0)
    {               
        Eigen::VectorXd X1 = X0;                                            ///< Current state as previous state in the iteration                   
        unsigned int order = B.cols();                                      ///< Specifying the mth order of Runge Kutta
        Eigen::VectorXd K[order];                                           ///< Array of m-th Runge Kutta slope k.

        // calculating Runge Kutta summand 
        for(unsigned int m = 0; m < order; m++){
            Eigen::VectorXd steps = X0;                                     ///< Initialization of the summands

            for(unsigned int j = 0; j < m; j++) steps += dt*B(m,j)*K[j];    // Loop to calculate the m-th slope
       
            K[m] = f(steps);                                                ///< Save the m-th slope
        }
        // Summing the product of slopes with their corresponding Butcher weight
        for(unsigned int i = 0; i < order; i++){
            X1 += dt*C[i]*K[i];
        }
        return X1;

    };

    /**
     * The Runge Kutta solver. Uses CalculateRKSummand to solve the ODE at different time steps.
     * The jump parameter allows us to store reduced number of data.
     * For exmaple if jump = 4, every 4th calculated value is stored as output.
     * To store all calculated steps, set jump=2.
     *
     * @param f     the right hand side function of the ODE.
     * @param X0    the initial value of the ODE.
     * @param jump  value for reducing the stored output
     * 
     * @return      std::vector of Eigen::VectorXd of integrated ODE solution.
    */
    template<typename Function>
    std::vector<Eigen::VectorXd> solve(Function &&f, const Eigen::VectorXd &X0, unsigned int jump=11)
    {
        Eigen::VectorXd SolutionBuffer[jump];                       ///< Creating a temporary buffer for the solutions
        SolutionBuffer[0] = X0;
        std::vector<Eigen::VectorXd> Solutions;                     ///< Create empty the solution vector
        Solutions.push_back(X0);                                    ///< Start by initial conditions
        int k = 1;

        // Loop over time steps to create solution at each new timestep
        for(unsigned int i = 0; i < num_steps; ++i){
            SolutionBuffer[k] = CalculateRKSummand(f,SolutionBuffer[k-1]);
            k++;
            if (k == jump){                                 
                Solutions.push_back(SolutionBuffer[k-1]);           ///< Storing every (jumps)-th value as output
                SolutionBuffer[0] = SolutionBuffer[k-1];            ///< Overwriting the buffer
                k = 1;
            };
        };
        return Solutions;
    };

};

#endif