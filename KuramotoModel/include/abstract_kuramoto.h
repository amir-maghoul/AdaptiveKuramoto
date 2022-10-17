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
	 * Tiles a matrix with a given vector row-wise
	 * 
	 * @param U Eigen::MatrixXd The vector from which the matrix is created
	 * 
	 * @return Eigen::MatrixXd The tiled matrix
	*/
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TileRows(
							const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)=0;

	/**
	 * Tiles a matrix with a given vector column-wise
	 * 
	 * @param U Eigen::MatrixXd The vector from which the matrix is created
	 * 
	 * @return Eigen::MatrixXd The tiled matrix
	*/
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TileCols(
							const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)=0;


	//documentation here
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Dynamics(
						const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)=0;

};



#endif