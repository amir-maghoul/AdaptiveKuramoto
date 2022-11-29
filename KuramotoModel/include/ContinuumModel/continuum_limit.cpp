#include "include/Headers/continuum_limit.h"

// /**
//  * Empty Constructor
// */
// template<class Function>
// ContinuumLimit<Function>::ContinuumLimit(){};

// /**
//  * Overloaded Constructor
// */
// template<class Function>
// ContinuumLimit<Function>::ContinuumLimit(/*Function W_IN, Function K_IN,*/ double ro_in, double t0_in, double t_end_in, double epsilon_in, double num_steps_in, int d_in)
// 		:	/*WC{W_IN}, KC0{K_IN},*/ ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, num_steps{num_steps_in}, d{d_in}{
// };

// /**
//  * Destructor
// */
// template<class Function>
// ContinuumLimit<Function>::~ContinuumLimit(){
// 	std::cout << "The class destructor was called for ContinuumLimit." << std::endl;
// 	};

// ContinuumLimit::ContinuumLimit(){};
ContinuumLimit::ContinuumLimit(/*Function W_IN, Function K_IN,*/ double ro_in, double t0_in, double t_end_in, double epsilon_in, double num_steps_in, int d_in)
		:	/*WC{W_IN}, KC0{K_IN},*/ ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, num_steps{num_steps_in}, d{d_in}{
};
ContinuumLimit::~ContinuumLimit(){std::cout << "The class destructor was called for ContinuumLimit." << std::endl;
	};
/***********************************************************************
 * Methods
*/

/**
 * Unpacks the output of run() method into a nested vector of phases and matrices.
 * First element is the vector of phases.
 * Second element is the vector of weights.
 * 
 * @param U Eigen::VectorXd the long vector of phases and flattened matrices
 * 
 * @return std::vector<std::vector> nested vector of phases and matrices
*/
std::vector<std::vector<Eigen::MatrixXd>> ContinuumLimit::UnpackSolveOutput(std::vector<Eigen::VectorXd> &U)
{
	std::vector<Eigen::MatrixXd> PHI;								///< Declaring the phase variable		
	std::vector<Eigen::MatrixXd> K;									///< Declaring the weight variable
	std::vector<std::vector<Eigen::MatrixXd>> output;

	for (unsigned int i=0; i < U.size(); i++)						///< For loop to divide up each vector in the input
	{
		PHI.push_back(U[i].head(d));								///< First d entries of the input vector are phases
		K.push_back((U[i].tail(d*d)));								///< Last d*d entries of the input vector are flattend weights
	};
	output.push_back(PHI);
	output.push_back(K);
	return output;
};

/**
 * Reads the first n elements of the input vector
 * 
 * @param U 	Eigen::VectorXd the long input vector
 * 
 * @return 		Eigen::VectorXd phases
*/
Eigen::VectorXd ContinuumLimit::UnpackPhases(const Eigen::VectorXd &U)
{	
	return U.head(d);
};

/**
 * Reads the last n^2 elements of the input vector and reshapes them into a matrix
 * 
 * @param U 	Eigen::VectorXd the long input vector
 * 
 * @return 		Eigen::MatrixXd the adjacency matrix
*/
Eigen::MatrixXd ContinuumLimit::UnpackWeights(const Eigen::VectorXd &U)
{
	return U.tail(d*d).reshaped(d, d);
};

/**
 * Packs a vector and a flattend matrix to create a long vector
 * 
 * @param U		Eigen::VectorXd the target vector in which the output value must be stored
 * @param V 	Eigen::VectorXd the input vector: the first n elements of the output
 * @param A 	Eigen::MatrixXd the input Matrix: the last n^2 elements of the output
 * 
 * @return 		Eigen::VectorXd
*/
Eigen::VectorXd ContinuumLimit::FlatConcatenate(Eigen::VectorXd &U, const Eigen::VectorXd &V, const Eigen::MatrixXd &A)
{
	U << V, A.reshaped(d*d, 1);
	return U;
};

/**
 * Discretizes the [0,1] interval into d discrete nodes
*/
Eigen::VectorXd ContinuumLimit::DiscretizeInterval()
{
	Eigen::VectorXd DiscreteInterval = Eigen::VectorXd::LinSpaced(d, 0.0, 1.0);
	return DiscreteInterval;
};

/**
 * Creates a square matrix of pairwise difference of elements of the given (mathematical) vector.
 * In order to do so, first creates matrices of copied columns and rows of the input vector and 
 * then returns the distance of the two matrices
 * 
 * @param U 	Eigen::MatrixXd The *column* vector from which the difference matrix is created
 * 
 * @return 		Eigen::MatrixXd
*/
Eigen::MatrixXd ContinuumLimit::DistanceMatrix(const Eigen::VectorXd &U)
{
	Eigen::MatrixXd RowTiled(U.size(), U.size());				///< Matrix created by copying the input row-wise
	Eigen::MatrixXd ColTiled(U.size(), U.size());				///< Matrix created by copying the input column-wise
	for (unsigned int i=0; i < U.size(); ++i)
	{
		RowTiled.row(i) = U.transpose();
		ColTiled.col(i) = U;
	} 
	return ColTiled - RowTiled;
};

Eigen::MatrixXd ContinuumLimit::Dynamics(Eigen::VectorXd &U, const Eigen::VectorXd &W, const double &a, const double &b)
{
// Unpacking the input vector
	Eigen::VectorXd PHI(d); 										///< The first N elements are the phases.
    Eigen::MatrixXd K(d, d);										///< The rest of the elements are the flattend adjacency matrix.
	
	PHI = UnpackPhases(U);											///< First n elements are the phases
	K 	= UnpackWeights(U);											///< last n^2 elements are the adjacency matrix

// Creating the interaction matrix of oscillators on each other
	Eigen::MatrixXd INTERACTION(d, d);								///< Initializing the interaction matrix between all pairs of Oscillators
	INTERACTION << DistanceMatrix(PHI);								///< Creating the difference matrix	

	Eigen::MatrixXd INTERACTION_PHI;								///< Oscillation part of interaction
	Eigen::MatrixXd INTERACTION_K;									///< Adaptation part of the interaction
	INTERACTION_PHI = (INTERACTION.array() + a).sin().matrix();		///< Applying the sine function and phase lag
	INTERACTION_K 	= (INTERACTION.array() + b).sin().matrix();		///< Applying the sine function and adaptation lag

// Creating the derivative equations
	Eigen::VectorXd PHI_DOT;										///< Initializing the derivative vector of phases
	Eigen::MatrixXd K_DOT;											///< Initializing the derivative matrix of adjacency coefficients

	Eigen::MatrixXd INTEGRAND_PHI;
	INTEGRAND_PHI = K.cwiseProduct(INTERACTION_PHI);				///< The operand of integral in the formula

	// ODE Formula: See the method documentation. Trapozoidal rule for matrices is used for numerical integration.
	PHI_DOT = W - (ro/d)*(IntegralSolvers::TrapMatrixin1D(INTEGRAND_PHI, 0, 1, d, 2, "y")); 		
	K_DOT 	= -epsilon*(K + INTERACTION_K);							///< Formula

// Repacking the outut and concatenating the results again
	FlatConcatenate(U, PHI_DOT, K_DOT);
	return U;
};

