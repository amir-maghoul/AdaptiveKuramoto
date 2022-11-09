#include "include/Headers/continuum_limit.h"


/**
 * Empty Constructor
*/
template<class Function>
ContinuumLimit<Function>::ContinuumLimit(){};

/**
 * Overloaded Constructor
*/
template<class Function>
ContinuumLimit<Function>::ContinuumLimit(Function W_IN, Function K_IN, double ro_in, double t0_in, double t_end_in, double epsilon_in, double num_steps_in, int d_in)
		:	W{W_IN}, K{K_IN}, ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, num_steps{num_steps_in}, d{d_in}{
};

/**
 * Destructor
*/
template<class Function>
ContinuumLimit<Function>::~ContinuumLimit(){
	std::cout << "The class destructor was called for ContinuumLimit." << std::endl;
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

template<class Function>
std::vector<std::vector<Eigen::MatrixXd>> ContinuumLimit<Function>::UnpackSolveOutput(std::vector<Eigen::VectorXd> &U)
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

Eigen::VectorXd DiscretizeInterval(){};

Eigen::VectorXd DiscretizePhases(){};

Eigen::MatrixXd DiscretizeWeights(){};

/**
 * Creates a square matrix of pairwise difference of elements of the given (mathematical) vector.
 * In order to do so, first creates matrices of copied columns and rows of the input vector and 
 * then returns the distance of the two matrices
 * 
 * @param U 	Eigen::MatrixXd The *column* vector from which the difference matrix is created
 * 
 * @return 		Eigen::MatrixXd
*/
template<class Function>
Eigen::MatrixXd ContinuumLimit<Function>::DistanceMatrix(const Eigen::VectorXd &U)
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

/**
 * Creates a vector of the interaction matrices of phase and weight dynamics for further calculation
 * 
 * @param f Function the phase density fucntion
 * 
 * @return std::vector<Eigen::MatrixXd> The vector of interaction matrices
*/
template<class Function>
Eigen::VectorXd ContinuumLimit<Function>::DiscreteInput(Function f, const double &a, const double &b)
{
	Eigen::VectorXd PHI(d);
	PHI = DiscretizePhases(f);										///< Discretize the continuous density of phases

	Eigen::MatrixXd DiscreteWeights(d,d);							///< Discretize Weights
	DiscreteWeights << DiscretizeWeights();

	Eigen::VectorXd U(d*d+d);
	U << PHI, DiscreteWeights.reshaped(d*d, 1);
	// Eigen::MatrixXd INTERACTION(d,d);
	// INTERACTION << DistanceMatrix(PHI);								///< Calculate the difference matrix for each entry point of phases

	// std::vector<Eigen::MatrixXd> result;
	// result.push_back((INTERACTION.array() + a).sin().matrix());		///< Interaction matrix for phase dynamics
	// result.push_back((INTERACTION.array() + b).sin().matrix());		///< Interaction matrix for weight dynamics

	return U;
};

template<class Function>
Eigen::VectorXd ContinuumLimit<Function>::PhaseDynamics(const double &a, const double &b)
{
	Eigen::VectorXd PHI_DOT(d);
	return PHI_DOT;
};

template<class Function>
Eigen::VectorXd ContinuumLimit<Function>::WeightDynamics(const double &a, const double &b)
{
	Eigen::MatrixXd WEIGHT_DOT;
	return WEIGHT_DOT;
};

template<class Function>
Eigen::MatrixXd ContinuumLimit<Function>::Dynamics(Eigen::VectorXd &U, const double &a, const double &b)
{
	// std::vector<Eigen::MatrixXd> InteractionVector = InteractionMatrix(f, a, b);
	// Eigen::MatrixXd INTERACTION_PHI = InteractionVector.at(0);
	// Eigen::MatrixXd INTERACTION_K = InteractionVector.at(1);

	// Eigen::VectorXd DiscreteFrequency(d);
	// DiscreteFrequency = DiscretizePhases(W);

	// Eigen::VectorXd PHI_DOT(d) 
	// PHI_DOT = PhaseDynamics();

	Eigen::MatrixXd INTERACTION_K;
	return INTERACTION_K;
};

template<class Function>
std::vector<std::vector<Eigen::MatrixXd>> ContinuumLimit<Function>::run(const Function &f0, const double &a, const double &b, unsigned int jump)
{

	Eigen::VectorXd U(d*d+d);
	U = DiscreteInput(f0);
	Eigen::VectorXd X0(d);
	X0 = U.head(d);

// Wrapping the dynamics for the given independent parameters a and b
	auto WrappedODE = [this, a, b] (Eigen::VectorXd &U)
	{
		return Dynamics(U, a, b);
	};
	std::vector<Eigen::VectorXd> result = ExplicitRKSolvers::Explicit4thOrderRK(WrappedODE, X0, num_steps, t0, t_end, jump);

// Unpack results into two vectors
	std::vector<std::vector<Eigen::MatrixXd>> output = UnpackSolveOutput(result);

	// TODO:
	// New functionality: change num_steps from within the method
	return output;
};

