#ifndef _DISCRETE_KURAMOTO_H_
#define _DISCRETE_KURAMOTO_H_

#include <vector>

class DiscreteKuramoto{
public:
	std::vector<double> w;					///< Natural frequencies
	std::vector<std::vector<double>> K0;	///< Initial adjacency matrix/Inital topology
	double ro;								///< Coupling strength
	double t0;								///< Initial integration time
	double t_end;							///< Final integration time
	double epsilon;							///< Slow dynamics coefficient
	double dt;								///< Integration time step

	DiscreteKuramoto();
	DiscreteKuramoto(std::vector<double> w_in, 
					 std::vector<std::vector<double>> K0_in, 
					 double ro_in 		= 0.2, 
					 double t0_in		= 0,
					 double t_end_in	= 40,
					 double epsilon_in	= 0.01,
					 double dt_in		= 0.01);	
	~DiscreteKuramoto();
	
};

#endif