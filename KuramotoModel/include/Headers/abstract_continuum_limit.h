#ifndef _CONTINUUM_LIMIT_H_
#define _CONTINUUM_LIMIT_H_

#include "include/Headers/abstract_kuramoto.h"

struct ContinuumLimit final : AbstractModel{

    // Attributes
	Eigen::VectorXd W;			///< Natural frequencies
	Eigen::MatrixXd K0;			///< Initial adjacency matrix/Inital topology
	double ro;					///< Coupling strength
	double t0;					///< Initial integration time
	double t_end;				///< Final integration time
	double epsilon;				///< Slow dynamics coefficient
	double num_steps;			///< Number of steps of the integration
	long n;						///< Number of Oscillators


	AbstractContinuumLimit();
	AbstractContinuumLimit(Eigen::VectorXd W_IN, Eigen::MatrixXd K0_IN,
					 double ro_in 			= 0.2, 
					 double t0_in			= 0,
					 double t_end_in		= 1,
					 double epsilon_in		= 0.01,
					 double num_steps_in	= 100);

	virtual ~AbstractContinuumLimit();
{   


};



#endif