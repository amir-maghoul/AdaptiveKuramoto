#ifndef _CONTINUUM_LIMIT_H_
#define _CONTINUUM_LIMIT_H_

#include "integrators.h"
#include "solvers.h"
#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <iostream>

template<class Function>
struct ContinuumLimit
{
    // Attributes
    Function W;                     ///< Natural frequency density
    Function K;                     ///< Graphon Kernel of the coupling
    double ro;					    ///< Coupling strength
	double t0;					    ///< Initial integration time
	double t_end;				    ///< Final integration time
	double epsilon;				    ///< Slow dynamics coefficient
	double num_steps;			    ///< Number of time steps of the integration
    int d;                          ///< The discretization fineness of space

    ContinuumLimit();
	ContinuumLimit(Function W_IN, Function K_IN,
					double ro_in 			= 0.2, 
					double t0_in			= 0,
					double t_end_in		    = 1,
					double epsilon_in		= 0.01,
					double num_steps_in	    = 100,
					int d_in				= 50);

	~ContinuumLimit();

/***********************************************************************
 * Methods
*/

std::vector<std::vector<Eigen::MatrixXd>> UnpackSolveOutput(std::vector<Eigen::VectorXd> &U);

Eigen::VectorXd DiscretizeInterval();

Eigen::VectorXd DiscretizePhases();

Eigen::MatrixXd DiscretizeWeights();

/* Creates a square matrix of pairwise difference of elements of the given (mathematical) vector. */
Eigen::MatrixXd DistanceMatrix(const Eigen::VectorXd &U);

/* Creates the interaction matrix for further calculation */
Eigen::VectorXd DiscreteInput(Function f, const double &a, const double &b);

Eigen::VectorXd PhaseDynamics(const double &a, const double &b);

Eigen::VectorXd WeightDynamics(const double &a, const double &b);

/* Creates the phase dynamics*/
Eigen::MatrixXd Dynamics(Eigen::VectorXd &U, const double &a, const double &b);

std::vector<std::vector<Eigen::MatrixXd>> run(const Function &X0, const double &a, const double &b, unsigned int jump);


};

#endif