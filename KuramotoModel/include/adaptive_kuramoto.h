#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include <include/abstract_kuramoto.h>
#include <Eigen/Dense>

struct AdaptiveKuramoto final : public AbstractModel{

/*
 * ******************************************************************
 * The empty constructor, constructor overloading and deconstructor *
 * ******************************************************************
*/
	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXd W_IN, 
					 Eigen::MatrixXd K0_IN,
					 double ro_in 			= 0.2, 
					 double t0_in			= 0,
					 double t_end_in		= 40,
					 double epsilon_in		= 0.01,
					 double dt_in			= 0.01);

	virtual ~AdaptiveKuramoto();

/*
**********************************************************************
 * Methods
**********************************************************************
*/
	virtual Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A);

	virtual Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U);

	virtual Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U);

	virtual Eigen::MatrixXd TileRows(const Eigen::VectorXd &U);
	
	virtual Eigen::MatrixXd TileCols(const Eigen::VectorXd &U);

	virtual Eigen::VectorXd Dynamics(Eigen::VectorXd &U, const double &a=0, const double &b=0);

};

#endif