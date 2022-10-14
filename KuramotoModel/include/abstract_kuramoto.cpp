#include "abstract_kuramoto.h"
#include <iostream>
#include <Eigen/Dense>

/*
 * *******************Abstract Class *********************
 * The empty constructor and the constructor overloading
 * *******************************************************
*/
AbstractModel::AbstractModel(){};
AbstractModel::AbstractModel(Eigen::VectorXd w_in, 
							 Eigen::MatrixXd K0_in, 
							 double ro_in, 
							 double t0_in,
							 double t_end_in,
							 double epsilon_in,
							 double dt_in)
	:	w{w_in}, K0{K0_in}, ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, dt{dt_in}{
};
/*
**********************************************************
 * Deconstructor
**********************************************************
*/
AbstractModel::~AbstractModel(){
	std::cout << "The class destructor was called for Abstract class." << std::endl;
	};

