#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include "solvers.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <eigen/Dense>

struct AdaptiveKuramoto{

	// Attributes
	Eigen::VectorXd W;			///< Natural frequencies
	Eigen::MatrixXd K0;			///< Initial adjacency matrix/Inital topology
	double ro;					///< Coupling strength
	double t0;					///< Initial integration time
	double t_end;				///< Final integration time
	double epsilon;				///< Slow dynamics coefficient
	double num_steps;			///< Number of steps of the integration
	long n;						///< Number of Oscillators

	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXd W_IN, Eigen::MatrixXd K0_IN,
					 double ro_in 			= 0.2, 
					 double t0_in			= 0,
					 double t_end_in		= 1,
					 double epsilon_in		= 0.01,
					 double num_steps_in	= 100);

	~AdaptiveKuramoto();

/***********************************************************************
 * Methods
*/	
	
	/* Unpacks the output of solve() method into a nested vector of phases and matrices. */
	std::vector<std::vector<Eigen::MatrixXd>> UnpackSolveOutput(std::vector<Eigen::VectorXd> &U);

	/* Packs a vector and a flattend matrix to create a long vector. */
	Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A);

	/*  Reads the first n elements of the input vector. */
	Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U);

	/* Reads the last n^2 elements of the input vector and reshapes them into a matrix. */
	Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U);

	/* Creates a square matrix of pairwise difference of elements of the given (mathematical) vector. */
	Eigen::MatrixXd DistanceMatrix(const Eigen::VectorXd &U);

	/* Describes the adaptive Kuramoto system dynamic ODEs. */
	Eigen::VectorXd Dynamics(Eigen::VectorXd &U, const double &a=0, const double &b=0);

	/* Solves the problem specified dynamics and stores the results of each timestep in a vector. */
	std::vector<std::vector<Eigen::MatrixXd>> run(const Eigen::VectorXd &X0, const double &a, const double &b, unsigned int jump);

	/* Computes the m-th order parameter. */
	std::vector<double> OrderParameter(Eigen::VectorXd PHI, const unsigned int &m);



};

#endif