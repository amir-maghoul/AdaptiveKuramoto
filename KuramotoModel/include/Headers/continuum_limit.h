#ifndef _CONTINUUM_LIMIT_H_
#define _CONTINUUM_LIMIT_H_

#include "solvers.h"
#include "integral_solver.h"
#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <iostream>

template<class Function>
struct ContinuumLimit
{
    // Attributes
    Function WC;                     ///< Natural frequency density
    Function KC0;                     ///< Graphon Kernel of the coupling
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

/* Unpacks the output of solve() method into a nested vector of phases and matrices. */
std::vector<std::vector<Eigen::MatrixXd>> UnpackSolveOutput(std::vector<Eigen::VectorXd> &U);

/*  Reads the first n elements of the input vector. */
Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U);

/* Reads the last n^2 elements of the input vector and reshapes them into a matrix. */
Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U);

/* Packs a vector and a flattend matrix to create a long vector. */
Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A);

/* Discretizes the [0, 1] interval into d nodes*/
Eigen::VectorXd DiscretizeInterval();

/* Discretizes the continuous phase function at d discrete nodes*/
Eigen::VectorXd DiscretizePhases(Function &Phi);

/* Discretized the continuous graphon into d*d matrix*/
Eigen::MatrixXd DiscretizeWeights();

/* Creates a square matrix of pairwise difference of elements of the given (mathematical) vector. */
Eigen::MatrixXd DistanceMatrix(const Eigen::VectorXd &U);

/* Uses the functions above to create a complete discretized system */
std::vector<Eigen::MatrixXd> DiscretizeSystem(Function &f0);

/* The second part of the dynamics of the Kuramoto model: weights */
Eigen::VectorXd WeightDynamics(const double &a, const double &b);

/* Creates the phase dynamics*/
Eigen::MatrixXd Dynamics(Eigen::VectorXd &U, Eigen::VectorXd &W, const double &a, const double &b);

std::vector<std::vector<Eigen::MatrixXd>> run(const Function &X0, const double &a, const double &b, unsigned int jump);


};

#endif