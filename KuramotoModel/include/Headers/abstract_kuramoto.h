#ifndef _KURAMOTO_ABSTRACT_H_
#define _KURAMOTO_ABSTRACT_H_

#include <iostream>
#include <Eigen/Dense>
#include <vector>

struct AbstractModel {

	// Attributes
	Eigen::VectorXd W;			///< Natural frequencies
	Eigen::MatrixXd K0;			///< Initial adjacency matrix/Inital topology
	double ro;					///< Coupling strength
	double t0;					///< Initial integration time
	double t_end;				///< Final integration time
	double epsilon;				///< Slow dynamics coefficient
	double num_steps;			///< Number of steps of the integration
	long n;						///< Number of Oscillators

	AbstractModel();
	AbstractModel(Eigen::VectorXd W_IN, Eigen::MatrixXd K0_IN, 
				  double ro_in 			= 0.2, 
				  double t0_in			= 0,
				  double t_end_in		= 1,
				  double epsilon_in		= 0.01,
				  double num_steps_in	= 100);
	virtual ~AbstractModel();

/*****************************************************************
 * Methods
*/
	/**
	 * Abstract to pack a vector and a flattend matrix to create a long vector
	*/
	virtual Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A)=0;

	/**
	 * Abstract to unpack phases from the long vector of adaptation input
	*/
	virtual Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U)=0;

	/**
	 * Abstract to unpack the adjacency matrix from the long vector of adaptation input
	*/
	virtual Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U)=0;

	/**
	 * Abstract to calculate the dynamics ODE of the adaptive Kuramoto system
	*/
	virtual Eigen::MatrixXd DistanceMatrix(const Eigen::VectorXd &U)=0;

	/**
	 * Abstract to calculate the dynamics ODE of the adaptive Kuramoto system
	*/
	virtual Eigen::VectorXd Dynamics(Eigen::VectorXd &U, const double &a, const double &b)=0;

	/**
	 * Abstract to solve the problem specified dynamical system
	*/
	virtual std::vector<std::vector<Eigen::MatrixXd>> run(const Eigen::VectorXd &X0, const double &a, const double &b, unsigned int jump)=0;

	/**
	 * Abstract to calculate the order parameter
	*/
	virtual std::vector<double> OrderParameter(Eigen::VectorXd &PHI, unsigned int &m)=0;

};



#endif