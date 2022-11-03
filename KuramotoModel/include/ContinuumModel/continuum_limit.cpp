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