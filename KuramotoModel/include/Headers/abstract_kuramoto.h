#ifndef _KURAMOTO_ABSTRACT_H_
#define _KURAMOTO_ABSTRACT_H_

#include <iostream>
#include <Eigen/Dense>
#include <vector>

struct AbstractModel {

	// Attributes
	Eigen::VectorXf W;			///< Natural frequencies
	Eigen::MatrixXf K0;			///< Initial adjacency matrix/Inital topology
	float ro;					///< Coupling strength
	float t0;					///< Initial integration time
	float t_end;				///< Final integration time
	float epsilon;				///< Slow dynamics coefficient
	float num_steps;			///< Number of steps of the integration
	long n;						///< Number of Oscillators

	AbstractModel();
	AbstractModel(Eigen::VectorXf W_IN, Eigen::MatrixXf K0_IN, 
				  float ro_in 			= 0.2, 
				  float t0_in			= 0,
				  float t_end_in		= 40,
				  float epsilon_in		= 0.01,
				  float num_steps_in	= 100);
	virtual ~AbstractModel();

/*****************************************************************
 * Methods
*/
	/**
	 * Template to pack a vector and a flattend matrix to create a long vector
	*/
	virtual Eigen::VectorXf FlatConcatenate(Eigen::VectorXf &U, const Eigen::VectorXf &V, const Eigen::MatrixXf &A)=0;

	/**
	 * Template to unpack phases from the long vector of adaptation input
	*/
	virtual Eigen::VectorXf UnpackPhases(const Eigen::VectorXf &U)=0;

	/**
	 * Template to unpack the adjacency matrix from the long vector of adaptation input
	*/
	virtual Eigen::MatrixXf UnpackWeights(const Eigen::VectorXf &U)=0;

	/**
	 * Template to calculate the dynamics ODE of the adaptive Kuramoto system
	*/
	virtual Eigen::MatrixXf DistanceMatrix(const Eigen::VectorXf &U)=0;

	/**
	 * Template to calculate the dynamics ODE of the adaptive Kuramoto system
	*/
	virtual Eigen::VectorXf Dynamics(Eigen::VectorXf &U, const float &a, const float &b)=0;

	/**
	 * Template to solve the problem specified dynamical system
	*/
	virtual std::vector<std::vector<Eigen::MatrixXf>> run(const Eigen::VectorXf &X0, const float &a, const float &b, unsigned int jump)=0;

};



#endif