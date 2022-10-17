#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include <include/abstract_kuramoto.h>
#include <Eigen/Dense>

class AdaptiveKuramoto final : public AbstractModel{
public:

/*
 * ******************* **********************************************
 * The empty constructor, constructor overloading and deconstructor *
 * ******************************************************************
*/
	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXd W_IN, 
					 Eigen::MatrixXd K0_IN, 
					 double ro_in 		= 0.2, 
					 double t0_in		= 0,
					 double t_end_in	= 40,
					 double epsilon_in	= 0.01,
					 double dt_in		= 0.01);

	virtual ~AdaptiveKuramoto();

/*
**********************************************************************
 * Methods
**********************************************************************
*/

	/**
	 * Tiles a matrix with a given vector row-wise
	 * 
	 * @param U Eigen::MatrixXd The row vector from which the matrix is created 
	 * 
	 * @return Eigen::MatrixXd The tiled matrix
	*/
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TileRows(
						const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U);
	
	/**
	 * Tiles a matrix with a given vector column-wise
	 * 
	 * @param U Eigen::MatrixXd The column vector from which the matrix is created
	 * 
	 * @return Eigen::MatrixXd The tiled matrix
	*/
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TileCols(
						const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U);

	
	//documentation here
	virtual Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Dynamics(
						const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U);

	
};

#endif