#ifndef _KURAMOTO_ABSTRACT_H_
#define _KURAMOTO_ABSTRACT_H_

#include <Eigen/Dense>

class AbstractModel {
public:

	// Attributes
	Eigen::VectorXd W;			///< Natural frequencies
	Eigen::MatrixXd K0;			///< Initial adjacency matrix/Inital topology
	double ro;					///< Coupling strength
	double t0;					///< Initial integration time
	double t_end;				///< Final integration time
	double epsilon;				///< Slow dynamics coefficient
	double dt;					///< Integration time step
	long n;						///< Number of oscillators


/*
***************************************************************
 * Empty constructor, constructor overloading and deconstructor
***************************************************************
*/
	AbstractModel();
	AbstractModel(Eigen::VectorXd W_IN, 
				  Eigen::MatrixXd K0_IN, 
				  double ro_in 		= 0.2, 
				  double t0_in		= 0,
				  double t_end_in	= 40,
				  double epsilon_in	= 0.01,
				  double dt_in		= 0.01);
	virtual ~AbstractModel();

/*
****************************************************************
 * Methods
****************************************************************
*/
	/**
	 * Template to pack a vector and a flattend matrix to create a long vector
	*/
	virtual Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A)=0;

	/**
	 * Template to unpack phases from the long vector of adaptation input
	*/
	virtual Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U)=0;

	/**
	 * Template to unpack the adjacency matrix from the long vector of adaptation input
	*/
	virtual Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U)=0;

	/**
	 * Template to create a square matrix by copying the row of the input vector as rows of the matrix
	*/
	virtual Eigen::MatrixXd TileRows(const Eigen::VectorXd &U)=0;

	/**
	 * Template to create a square matrix by copying the columns of the input vector as columns of the matrix
	*/
	virtual Eigen::MatrixXd TileCols(const Eigen::VectorXd &U)=0;

	/**
	 * Template to calculate the dynamics ODE of the adaptive Kuramoto system
	*/
	virtual Eigen::VectorXd Dynamics(Eigen::VectorXd &U, const double &a, const double &b)=0;

};



#endif