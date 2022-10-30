#include "include/Headers/adaptive_kuramoto.h"

/**
 * Empty Constructor
*/
AdaptiveKuramoto::AdaptiveKuramoto(){};

/**
 * Overloaded Constructor
*/
AdaptiveKuramoto::AdaptiveKuramoto(Eigen::VectorXf W_IN, Eigen::MatrixXf K0_IN, float ro_in, float t0_in, float t_end_in, float epsilon_in, float num_steps_in)
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
 * Unpacks the output of solve() method into a nested vector of phases and matrices.
 * First element is the vector of phases.
 * Second element is the vector of weights.
 * 
 * @param U Eigen::VectorXf the long vector of phases and flattened matrices
 * 
 * @return std::vector<std::vector> nested vector of phases and matrices
*/
std::vector<std::vector<Eigen::MatrixXf>> AdaptiveKuramoto::UnpackSolveOutput(std::vector<Eigen::VectorXf> &U)
{
	std::vector<Eigen::MatrixXf> PHI;								///< Declaring the phase variable		
	std::vector<Eigen::MatrixXf> K;									///< Declaring the weight variable
	std::vector<std::vector<Eigen::MatrixXf>> output;

	for (unsigned int i=0; i < U.size(); i++)						///< For loop to divide up each vector in the input
	{
		PHI.push_back(U[i].head(n));								///< First n entries of the input vector are phases
		K.push_back((U[i].tail(n*n)));								///< Last n*n entries of the input vector are flattend weights
	};
	output.push_back(PHI);
	output.push_back(K);
	return output;
};

/**
 * Packs a vector and a flattend matrix to create a long vector
 * 
 * @param U	Eigen::VectorXf the target vector in which the output value must be stored
 * @param V Eigen::VectorXf the input vector: the first n elements of the output
 * @param A Eigen::MatrixXf the input Matrix: the last n^2 elements of the output
 * 
 * @return Eigen::VectorXf
*/
Eigen::VectorXf AdaptiveKuramoto::FlatConcatenate(Eigen::VectorXf &U, const Eigen::VectorXf &V, const Eigen::MatrixXf &A)
{
	U << V, A.reshaped(n*n, 1);
	return U;
};

/**
 * Reads the first n elements of the input vector
 * 
 * @param U Eigen::VectorXf the long input vector
 * 
 * @return Eigen::VectorXf phases
*/
Eigen::VectorXf AdaptiveKuramoto::UnpackPhases(const Eigen::VectorXf &U)
{	
	return U.head(n);
};

/**
 * Reads the last n^2 elements of the input vector and reshapes them into a matrix
 * 
 * @param U Eigen::VectorXf the long input vector
 * 
 * @return Eigen::MatrixXf the adjacency matrix
*/
Eigen::MatrixXf AdaptiveKuramoto::UnpackWeights(const Eigen::VectorXf &U)
{
	return U.tail(n*n).reshaped(n, n);
};

/**
 * Creates a square matrix of pairwise difference of elements of the given (mathematical) vector.
 * In order to do so, first creates matrices of copied columns and rows of the input vector and 
 * then returns the distance of the two matrices
 * 
 * @param U Eigen::MatrixXf The *column* vector from which the difference matrix is created
 * 
 * @return Eigen::MatrixXf
*/
Eigen::MatrixXf AdaptiveKuramoto::DistanceMatrix(const Eigen::VectorXf &U)
{
	Eigen::MatrixXf RowTiled(U.size(), U.size());				///< Matrix created by copying the input row-wise
	Eigen::MatrixXf ColTiled(U.size(), U.size());				///< Matrix created by copying the input column-wise
	for (unsigned int i=0; i < U.size(); ++i)
	{
		RowTiled.row(i) = U.transpose();
		ColTiled.col(i) = U;
	} 
	return ColTiled - RowTiled;
}

/**
 * Describes the adaptive Kuramoto system dynamic ODEs.
 * In order to calculate the ODE, an interaction matrix is created which is the matrix of sin() function applied to 
 * difference matrix: sin(phi_i - phi_j) as a matrix. Then to calculate the sum part of the formula, an elementwise 
 * multiplication of adjacency matrix with the interaction matrix is calculated and it is summed over the columns.
 * (in Eigen, sum over colums is calculated using M.rowwise().sum())
 * 
 * v_ij = sin(phi_i - phi_j + a)
 * dot(phi) = w + (A .* V).sum(axis=1)
 * 
 * @param U Eigen::MatrixXf The *column* vector of phases and flattend adjacency matrix concatenated
 * @param a double coupling phase lag
 * @param b double coupling adaptation lag
 * 
 * @return Eigen::MatrixXf The concatenated vector of derivatives of phases and flattened derivative of adjacency matrix
*/
Eigen::VectorXf AdaptiveKuramoto::Dynamics(Eigen::VectorXf &U, const float &a, const float &b)
{
// Unpacking the input vector
	Eigen::VectorXf PHI(n); 										///< The first N elements are the phases.
    Eigen::MatrixXf K(n, n);										///< The rest of the elements are the flattend adjacency matrix.
	
	PHI = UnpackPhases(U);											///< First n elements are the phases
	K 	= UnpackWeights(U);											///< last n^2 elements are the adjacency matrix

// Creating the interaction matrix of oscillators on each other
	Eigen::MatrixXf INTERACTION(n, n);								///< Initializing the interaction matrix between all pairs of Oscillators
	INTERACTION << DistanceMatrix(PHI);								///< Creating the difference matrix	

	Eigen::MatrixXf INTERACTION_PHI;								///< Oscillation part of interaction
	Eigen::MatrixXf INTERACTION_K;									///< Adaptation part of the interaction
	INTERACTION_PHI = (INTERACTION.array() + a).sin().matrix();		///< Applying the sine function and phase lag
	INTERACTION_K 	= (INTERACTION.array() + b).sin().matrix();		///< Applying the sine function and adaptation lag

// Creating the derivative equations
	Eigen::VectorXf PHI_DOT;										///< Initializing the derivative vector of phases
	Eigen::MatrixXf K_DOT;											///< Initializing the derivative matrix of adjacency coefficients

	PHI_DOT = W + (ro/n)*(K.cwiseProduct(INTERACTION_PHI)).rowwise().sum(); ///< Formula: See the method documentation
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
 * @param U0 Eigen::VectorXf the initial state of the system
 * @param a double coupling phase lag
 * @param b double coupling adaptation lag
 * 
 * @return std::vector<Eigen::VectorXf> the state of the system at each timestep
*/
std::vector<std::vector<Eigen::MatrixXf>> AdaptiveKuramoto::run(const Eigen::VectorXf &X0, const float &a, const float &b, unsigned int jump)
{
// Packing the input of the dyanamics
	Eigen::VectorXf U0(n*n+n, 1);
	FlatConcatenate(U0, X0, K0);										///< Put together the inital phases and flattend inital weight matrix

// Wrapping the dynamics for the given independent parameters a and b
	auto WrappedODE = [this, a, b] (Eigen::VectorXf &U)
	{
		return Dynamics(U, a, b);
	};
	std::vector<Eigen::VectorXf> result = ExplicitRKSolvers::Explicit4thOrderRK(WrappedODE, U0, num_steps, t0, t_end);

// Unpack results into two vectors
	std::vector<std::vector<Eigen::MatrixXf>> output = UnpackSolveOutput(result);

	// TODO:
	// New functionality: change num_steps from within the method
	return output;
};


