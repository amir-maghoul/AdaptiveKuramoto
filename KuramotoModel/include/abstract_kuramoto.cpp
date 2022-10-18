#include "include/abstract_kuramoto.h"
#include <iostream>
// #include <Eigen/Dense>

/*
 * ******************* Abstract Class *******************************
 * The empty constructor, constructor overloading and deconstructor *
 * ******************************************************************
*/
AbstractModel::AbstractModel(){};
AbstractModel::AbstractModel(Eigen::VectorXd W_IN, 
							 Eigen::MatrixXd K0_IN, 
							 double ro_in, 
							 double t0_in,
							 double t_end_in,
							 double epsilon_in,
							 double num_steps_in)
	:	W{W_IN}, K0{K0_IN}, ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, num_steps{num_steps_in}, n{W.size()}{
};
AbstractModel::~AbstractModel(){
	std::cout << "The class destructor was called for Abstract class." << std::endl;
	};

/*******************************************************************
 * Methods
********************************************************************/
// documentation here
// Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> AbstractModel::dynamics(){};

