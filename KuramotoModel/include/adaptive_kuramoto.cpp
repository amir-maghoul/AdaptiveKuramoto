#include "include/adaptive_kuramoto.h"
#include "include/abstract_kuramoto.h"
#include <iostream>

/*
 * *******************Adaptive Kuramoto *******************
 * The empty constructor and the constructor overloading
 *********************************************************
 */
AdaptiveKuramoto::AdaptiveKuramoto(){};
AdaptiveKuramoto::AdaptiveKuramoto(Eigen::VectorXd w_in, 
								   Eigen::MatrixXd K0_in, 
								   double ro_in, 
								   double t0_in,
								   double t_end_in,
								   double epsilon_in,
								   double dt_in)
	:	AbstractModel(w_in, K0_in, ro_in, t0_in, t_end_in, epsilon_in, dt_in){
};

/**********************************************************
 * Deconstructor
***********************************************************/
AdaptiveKuramoto::~AdaptiveKuramoto(){
	std::cout << "The class destructor was called for AdaptiveKuramoto." << std::endl;
	};

/***********************************************************
 * Methods
***********************************************************/
