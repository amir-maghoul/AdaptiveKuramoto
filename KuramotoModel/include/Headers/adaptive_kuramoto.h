#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include "abstract_kuramoto.h"
#include "solvers.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

struct AdaptiveKuramoto final : AbstractModel{

	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXf W_IN, Eigen::MatrixXf K0_IN,
					 float ro_in 			= 0.2, 
					 float t0_in			= 0,
					 float t_end_in			= 1,
					 float epsilon_in		= 0.01,
					 float num_steps_in		= 100);

	virtual ~AdaptiveKuramoto();

/***********************************************************************
 * Methods
*/
	std::vector<std::vector<Eigen::MatrixXf>> UnpackSolveOutput(std::vector<Eigen::VectorXf> &U);

	virtual Eigen::VectorXf FlatConcatenate(Eigen::VectorXf &U, const Eigen::VectorXf &V, const Eigen::MatrixXf &A);

	virtual Eigen::VectorXf UnpackPhases(const Eigen::VectorXf &U);

	virtual Eigen::MatrixXf UnpackWeights(const Eigen::VectorXf &U);

	virtual Eigen::MatrixXf DistanceMatrix(const Eigen::VectorXf &U);

	virtual Eigen::VectorXf Dynamics(Eigen::VectorXf &U, const float &a=0, const float &b=0);

	virtual std::vector<std::vector<Eigen::MatrixXf>> run(const Eigen::VectorXf &X0, const float &a, const float &b, unsigned int jump);


};

#endif