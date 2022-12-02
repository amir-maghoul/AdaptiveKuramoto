#ifndef _CONTINUUM_LIMIT_H_
#define _CONTINUUM_LIMIT_H_

#include "solvers.h"
#include "integral_solver.h"
#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <iostream>

// template<class Function>
struct ContinuumLimit
{
    // Attributes
    // Function WC;                    ///< Natural frequency density
    // Function KC0;                   ///< Graphon Kernel of the coupling
    double ro;					    ///< Coupling strength
	double t0;					    ///< Initial integration time
	double t_end;				    ///< Final integration time
	double epsilon;				    ///< Slow dynamics coefficient
	double num_steps;			    ///< Number of time steps of the integration
    int d;                          ///< The discretization fineness of space

    // ContinuumLimit();
	ContinuumLimit(// Function W_IN, Function K_IN,
					double ro_in 			= 0.2, 
					double t0_in			= 0,
					double t_end_in		    = 1,
					double epsilon_in		= 0.01,
					double num_steps_in	    = 1000,
					int d_in				= 50);

	~ContinuumLimit();

/*
*/
/***********************************************************************
 * Non-templated method declarations
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

/* Creates a square matrix of pairwise difference of elements of the given (mathematical) vector. */
Eigen::MatrixXd DistanceMatrix(const Eigen::VectorXd &U);

/* Creates the phase dynamics*/
Eigen::MatrixXd Dynamics(Eigen::VectorXd &U, const Eigen::VectorXd &W, const double &a, const double &b);

/*
*/
/** *************************************************************************
 * Template methods declarations and definitions *
 */

/**
 * Discretizes the continuous phase function at discrete nodes
 * 
 * @param Phi 		Function: The continuous phase function
 * 
 * @return 			Eigen::VectorXd: Vector of discretized phases
*/
template<typename Function>
Eigen::VectorXd DiscretizePhases(Function &&Phi)
{
	Eigen::VectorXd DiscretePhases(d, 1);
	for (size_t i=0; i < d; ++i)
	{
		DiscretePhases(i) = Phi(i);
	}
	return DiscretePhases;
};

/**
 * Discretizes the continuous graphon into a d*d matrix
*/
template<typename Function>
Eigen::MatrixXd DiscretizeWeights(Function &KC0){
	Eigen::VectorXd DiscreteInterval = DiscretizeInterval();
	Eigen::MatrixXd DiscretizedWeight(d,d);
	for (size_t i=0;i<d;++i){
		for (size_t j=0;j<d;++j){
			DiscretizedWeight(i, j) = KC0(DiscreteInterval(i), DiscreteInterval(j));
		}

	}
	return DiscretizedWeight;
};

/** 
 * Uses the functions above to create a complete discretized system
 * 
 * @param f		Function the initial phases
 * @param a 	double coupling phase lag
 * @param b 	double coupling adaptation lag
 * 
 * @return 		Eigen::VectorXd of the time derivative of the long input vector 
*/
template<typename F1, typename F2, typename F3>
std::vector<Eigen::MatrixXd> DiscretizeSystem(F1 &&f0, F2 &&WC, F3 &&KC)
{
	Eigen::VectorXd PHI(d);								///< Discretize intial phases
	PHI = DiscretizePhases(f0);

	Eigen::VectorXd W(d);								///< Discretize Natural frequency
	W = DiscretizePhases(WC);

	Eigen::MatrixXd WEIGHTS(d, d);						///< Discretize Weights
	WEIGHTS = DiscretizeWeights(KC);

	std::vector<Eigen::MatrixXd> system;				///< Store everything in a vector
	system.push_back(PHI);
	system.push_back(W);
	system.push_back(WEIGHTS);

	return system;
};

/**
 * The run function for the ODE solver. This creates the needed input for Dynamics() method and call it.
 * 
 * @param f0 		F Initial phase density
 * @param WC0		F Initial natural frequency density
 * @param KC0 		G Initial weight density
 * @param a 		double phase lag
 * @param b 		double weight lag
 * @param jump		int the length of solution buffer: only every jump-th step is stored. To store all steps set jump = 2
 * 
 * @return std::vector<std::vector<Eigen::MatrixXd>> the state of the system at each timestep as a nested vector
*/
template<typename F1, typename F2, typename F3>
std::vector<std::vector<Eigen::MatrixXd>> run(F1 &&f0, F2 &&WC0, F3 &&KC0, const double &a=0, const double &b=0, unsigned int jump=2)
{	
// Creating a discrete system out of the continuous one
	std::vector<Eigen::MatrixXd> system;
	system = DiscretizeSystem(f0, WC0, KC0);

	Eigen::VectorXd X0(d);
	X0 = system.at(0);

	Eigen::VectorXd W(d);
	W = system.at(1);

	Eigen::MatrixXd K0(d, d);
	K0 << system.at(2);

// Creating long vector for the input of dynamics
	Eigen::VectorXd U0(d*d+d);
	FlatConcatenate(U0, X0, K0);

// Wrapping the dynamics for the given independent parameters a and b
	auto WrappedODE = [this, W, a, b] (Eigen::VectorXd &U)
	{
		return Dynamics(U, W, a, b);
	};

	std::vector<Eigen::VectorXd> result = ExplicitRKSolvers::Explicit4thOrderRK(WrappedODE, U0, num_steps, t0, t_end, jump);

// Unpack results into two vectors
	std::vector<std::vector<Eigen::MatrixXd>> output = UnpackSolveOutput(result);

	return output;
};


};

#endif