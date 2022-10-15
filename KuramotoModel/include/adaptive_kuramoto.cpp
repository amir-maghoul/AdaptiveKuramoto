#include "include/adaptive_kuramoto.h"
#include "include/abstract_kuramoto.h"
#include <iostream>

/*
 * *******************Abstract Class ********************************
 *
 * The empty constructor, constructor overloading and deconstructor *
 * 
 * ******************************************************************
*/
AdaptiveKuramoto::AdaptiveKuramoto(){};
AdaptiveKuramoto::AdaptiveKuramoto(Eigen::VectorXd W_IN, 
								   Eigen::MatrixXd K0_IN, 
								   double ro_in, 
								   double t0_in,
								   double t_end_in,
								   double epsilon_in,
								   double dt_in)
	:	AbstractModel(W_IN, K0_IN, ro_in, t0_in, t_end_in, epsilon_in, dt_in){
};
AdaptiveKuramoto::~AdaptiveKuramoto(){
	std::cout << "The class destructor was called for AdaptiveKuramoto." << std::endl;
	};

/*******************************************************************
 * 
 * Methods
 * 
********************************************************************/
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> AdaptiveKuramoto::dynamics(){
	return K0;
};

