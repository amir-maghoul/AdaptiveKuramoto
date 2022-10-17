#include "include/adaptive_kuramoto.h"
#include "include/abstract_kuramoto.h"
#include <iostream>
#include <cmath>

/*
 * *******************Abstract Class ********************************
 * The empty constructor, constructor overloading and deconstructor *
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
 * Methods
********************************************************************/

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> AdaptiveKuramoto::TileRows(
							const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)
{
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> T(U.size(), U.size());
	for (unsigned int i=0; i < U.size(); ++i) T.row(i) = U;
	return T;

};

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> AdaptiveKuramoto::TileCols(
							const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)
{
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> T(U.size(), U.size());
	for (unsigned int i=0; i < U.size(); ++i) T.col(i) << U;
	return T;

};

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> AdaptiveKuramoto::Dynamics(
							const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &U)
{	
	int size = W.size();													///< Number of Oscillators.
	Eigen::Matrix<double, Eigen::Dynamic, 1> PHI(size);						///< The first N elements are the phases.
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> K(size, size);	///< The rest of the elements are the flattend adjacency matrix.
	
	// Defining new variables for each slice and put their values in.
	PHI << U.topRows(size);
	K << U.bottomRows(size*size).reshaped(size, size);

	Eigen::Matrix<double, Eigen::Dynamic, 1> PHI_DOT;						///< Initializing the derivative vector of phases
	Eigen::Matrix<double, Eigen::Dynamic, 1> K_DOT;							///< Initializing the derivative matrix of adjacency coefficients



	Eigen::Matrix<double, Eigen::Dynamic, 1> TRANSACTION;					///< Initializing the transaction matrix between all pairs of Oscillators
	// TRANSACTION << 


	// PHI_DOT << W + 


	return K;
};

