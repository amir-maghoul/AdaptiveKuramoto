#ifndef _ADAPTIVE_KURAMOTO_H_
#define _ADAPTIVE_KURAMOTO_H_

#include <include/abstract_kuramoto.h>
#include <Eigen/Dense>


class AdaptiveKuramoto : public AbstractModel{
public:

	// Empty Constructor and Constructor overloading
	AdaptiveKuramoto();
	AdaptiveKuramoto(Eigen::VectorXd w_in, 
					 Eigen::MatrixXd K0_in, 
					 double ro_in 		= 0.2, 
					 double t0_in		= 0,
					 double t_end_in	= 40,
					 double epsilon_in	= 0.01,
					 double dt_in		= 0.01);

	// Deconstructor
	~AdaptiveKuramoto();
	
};

#endif