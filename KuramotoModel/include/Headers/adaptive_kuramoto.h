#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include "abstract_kuramoto.h"
#include "solvers.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

struct AdaptiveKuramoto final : public AbstractModel{

	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXd W_IN, Eigen::MatrixXd K0_IN,
					 double ro_in 			= 0.2, 
					 double t0_in			= 0,
					 double t_end_in		= 40,
					 double epsilon_in		= 0.01,
					 double num_steps_in	= 100);

	virtual ~AdaptiveKuramoto();

/***********************************************************************
 * Methods
*/
	std::vector<std::vector<Eigen::MatrixXd>> UnpackSolveOutput(std::vector<Eigen::VectorXd> &U);

	virtual Eigen::VectorXd FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A);

	virtual Eigen::VectorXd UnpackPhases(const Eigen::VectorXd &U);

	virtual Eigen::MatrixXd UnpackWeights(const Eigen::VectorXd &U);

	virtual Eigen::MatrixXd TileRows(const Eigen::VectorXd &U);
	
	virtual Eigen::MatrixXd TileCols(const Eigen::VectorXd &U);

	virtual Eigen::VectorXd Dynamics(Eigen::VectorXd &U, const double &a=0, const double &b=0);

	virtual std::vector<std::vector<Eigen::MatrixXd>>  run(const Eigen::VectorXd &X0, const double &a, const double &b);


};

#endif