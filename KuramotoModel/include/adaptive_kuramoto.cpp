#include "include/adaptive_kuramoto.h"
#include "include/abstract_kuramoto.h"
#include "include/solvers.h"
#include <iostream>
#include <cmath>
#include <algorithm>

/**
 * Empty Constructor
*/
AdaptiveKuramoto::AdaptiveKuramoto(){};

/**
 * Overloaded Constructor
*/
AdaptiveKuramoto::AdaptiveKuramoto(Eigen::VectorXd W_IN, Eigen::MatrixXd K0_IN, double ro_in, double t0_in, double t_end_in, double epsilon_in, double num_steps_in)
	:	AbstractModel(W_IN, K0_IN, ro_in, t0_in, t_end_in, epsilon_in, num_steps_in){};

/**
 * Destructor
*/
AdaptiveKuramoto::~AdaptiveKuramoto(){
	std::cout << "The class destructor was called for AdaptiveKuramoto." << std::endl;
	};

/*******************************************************************
 * Methods
*/

/**
 * Packs a vector and a flattend matrix to create a long vector
 * 
 * @param U	Eigen::VectorXd the target vector in which the output value must be stored
 * @param V Eigen::VectorXd the input vector: the first n elements of the output
 * @param A Eigen::MatrixXd the input Matrix: the last n^2 elements of the output
 * 
 * @return Eigen::VectorXd
*/
Eigen::VectorXd AdaptiveKuramoto::FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A)
{
	U << V, A.reshaped(n*n, 1);
	return U;
};

/**
 * Reads the first n elements of the input vector
 * 
 * @param U Eigen::VectorXd the long input vector
 * 
 * @return Eigen::VectorXd phases
*/
Eigen::VectorXd AdaptiveKuramoto::UnpackPhases(const Eigen::VectorXd &U)
{	
	return U.head(n);
};

/**
 * Reads the last n^2 elements of the input vector and reshapes them into a matrix
 * 
 * @param U Eigen::VectorXd the long input vector
 * 
 * @return Eigen::MatrixXd the adjacency matrix
*/
Eigen::MatrixXd AdaptiveKuramoto::UnpackWeights(const Eigen::VectorXd &U)
{
	return U.tail(n*n).reshaped(n, n);
};

/**
 * Unpacks the output of solve() method into a nested vector of phases and matrices
 * 
 * @param U Eigen::VectorXd the long vector of phases and flattened matrices
 * 
 * @return std::vector<std::vector> nested vector of phases and matrices
*/
std::vector<std::vector<Eigen::MatrixXd>> AdaptiveKuramoto::UnpackSolveOutput(std::vector<Eigen::VectorXd> &U)
{
	std::vector<Eigen::MatrixXd> PHI;								///< Declaring the phase variable		
	std::vector<Eigen::MatrixXd> K;									///< Declaring the weight variable
	std::vector<std::vector<Eigen::MatrixXd>> output;

	for (unsigned int i=0; i < U.size(); i++)						///< For loop to divide up each vector in the input
	{
		PHI.push_back(U[i].head(n));								///< First n entries of the input vector are phases
		K.push_back((U[i].tail(n*n)).reshaped(n, n));				///< Last n*n entries of the input vector are flattend weights
	};
	output.push_back(PHI);
	output.push_back(K);
	return output;
};

/**
 * Creates a square matrix by copying the row of the input vector as rows of the matrix
 * The number of rows is equal to the number of columns of the vector.
 * 
 * @param U Eigen::MatrixXd The row vector from which the matrix is created
 * 
 * @return Eigen::MatrixXd The tiled matrix
*/
Eigen::MatrixXd AdaptiveKuramoto::TileRows(const Eigen::VectorXd &U)
{
	Eigen::MatrixXd T(U.size(), U.size());
	for (unsigned int i=0; i < U.size(); ++i) T.row(i) = U;
	return T;
};

/**
 * Creates a square matrix by copying the columns of the input vector as columns of the matrix
 * The number of columns is equal to the number of rows of the vector.
 * 
 * @param U Eigen::MatrixXd The column vector from which the matrix is created
 * 
 * @return Eigen::MatrixXd The tiled matrix
*/
Eigen::MatrixXd AdaptiveKuramoto::TileCols(const Eigen::VectorXd &U)
{
	Eigen::MatrixXd T(U.size(), U.size());
	for (unsigned int i=0; i < U.size(); ++i) T.col(i) << U;
	return T;
};

/**
 * Describes the adaptive Kuramoto system dynamic ODEs.
 * In order to calculate the ODE, an interaction matrix is created which is the matrix of sin() function applied to 
 * difference matrix: sin(phi_i - phi_j) as a matrix. Then to calculate the sum part of the formula, an elementwise 
 * multiplication of adjacency matrix with the interaction matrix is calculated and it is summed over the columns.
 * 
 * v_ij = sin(phi_i - phi_j + a)
 * dot(phi) = w + (A .* V).sum(axis=1)
 * 
 * @param U Eigen::MatrixXd The *column* vector of phases and flattend adjacency matrix concatenated
 * @param a double coupling phase lag
 * @param b double coupling adaptation lag
 * 
 * @return Eigen::MatrixXd The concatenated vector of derivatives of phases and flattened derivative of adjacency matrix
*/
Eigen::VectorXd AdaptiveKuramoto::Dynamics(Eigen::VectorXd &U, const double &a, const double &b)
{
// Unpacking the input vector
	Eigen::VectorXd PHI(n); 										///< The first N elements are the phases.
    Eigen::MatrixXd K(n, n);										///< The rest of the elements are the flattend adjacency matrix.
	
	PHI = UnpackPhases(U);											///< First n elements are the phases
	K 	= UnpackWeights(U);											///< last n^2 elements are the adjacency matrix

// Creating the interaction matrix of oscillators on each other
	Eigen::MatrixXd INTERACTION(n, n);								///< Initializing the interaction matrix between all pairs of Oscillators
	INTERACTION << TileCols(PHI) - TileRows(PHI.transpose());		///< Creating the difference matrix
	
	Eigen::MatrixXd INTERACTION_PHI;								///< Oscillation part of interaction
	Eigen::MatrixXd INTERACTION_K;									///< Adaptation part of the interaction
	INTERACTION_PHI = (INTERACTION.array() + a).sin().matrix();		///< Applying the sine function and phase lag
	INTERACTION_K 	= (INTERACTION.array() + b).sin().matrix();		///< Applying the sine function and adaptation lag

// Creating the derivative equations
	Eigen::VectorXd PHI_DOT;										///< Initializing the derivative vector of phases
	Eigen::MatrixXd K_DOT;											///< Initializing the derivative matrix of adjacency coefficients

	PHI_DOT = W.transpose() + (ro/n)*(K.cwiseProduct(INTERACTION_PHI)).colwise().sum(); ///< Formula: See the method documentation
	K_DOT 	= -epsilon*(K + INTERACTION_K);							///< Formula

// Repacking the outut and concatenating the results again
	FlatConcatenate(U, PHI_DOT, K_DOT);
	return U;
};

/**
 * Solves the problem specified dynamics and stores the results of each timestep in a vector. 
 * The initial adjacency matrix is the same as initial topology of the system, therefore the 
 * class attribute K0.
 * 
 * @param U0 Eigen::VectorXd the initial state of the system
 * @param a double coupling phase lag
 * @param b double coupling adaptation lag
 * 
 * @return std::vector<Eigen::VectorXd> the state of the system at each timestep
*/
std::vector<std::vector<Eigen::MatrixXd>> AdaptiveKuramoto::run(const Eigen::VectorXd &X0, const double &a, const double &b)
{
// Packing the input of the dyanamics
	Eigen::VectorXd U0(n*n+n, 1);
	FlatConcatenate(U0, X0, K0);										///< Put together the inital phases and flattend inital weight matrix

// Wrapping the dynamics for the given independent parameters a and b
	auto WrappedODE = [this, a, b] (Eigen::VectorXd &U)
	{
		return Dynamics(U, a, b);
	};
	std::vector<Eigen::VectorXd> result = ExplicitRKSolvers::Explicit4thOrderRK(WrappedODE, U0, num_steps, t0, t_end);

// Unpack results into two vectors
	std::vector<std::vector<Eigen::MatrixXd>> output = UnpackSolveOutput(result);

	// TODO:
	// New functionality: change num_steps from within the method
	return output;
};


