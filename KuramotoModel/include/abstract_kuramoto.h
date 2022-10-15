#ifndef _KURAMOTO_ABSTRACT_H_
#define _KURAMOTO_ABSTRACT_H_

#include <Eigen/Dense>

class AbstractModel {
public:

	// Attributes
	Eigen::VectorXd W;			///< Natural frequencies
	Eigen::MatrixXd K0;			///< Initial adjacency matrix/Inital topology
	double ro;					///< Coupling strength
	double t0;					///< Initial integration time
	double t_end;				///< Final integration time
	double epsilon;				///< Slow dynamics coefficient
	double dt;					///< Integration time step

	// Methods
	//virtual Eigen::Matrix dynamics() = 0; //Solution: Template classes?


	// Empty Constructor and Constructor overloading
	AbstractModel();
	AbstractModel(Eigen::VectorXd W_IN, 
				  Eigen::MatrixXd K0_IN, 
				  double ro_in 		= 0.2, 
				  double t0_in		= 0,
				  double t_end_in	= 40,
				  double epsilon_in	= 0.01,
				  double dt_in		= 0.01);

	// Deconstructor
	virtual ~AbstractModel();
};



#endif