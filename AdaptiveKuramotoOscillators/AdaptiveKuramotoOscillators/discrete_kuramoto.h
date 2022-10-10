#ifndef _DISCRETE_KURAMOTO_H_
#define _DISCRETE_KURAMOTO_H_

#include <vector>



/* 
* Class of Classical Adaptive Kuramoto Model
*/
class DiscreteKuramoto{
public: 
	int N; 										///< Number of oscillators
	std::vector<double> w;						///< Natural frequency
	std::vector<std::vector<double>> K0;		///< Initial adjacency matrix/Initial network topology
	double ro;									///< Coupling strength
	double t0;									///< The simulation starting time
	double t_end; 								///< The simulation end time
	double epsilon;								///< Slow dynamics coefficient
	double dt;									///< Time step

	DiscreteKuramoto();
	DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in);
	DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in, double ro_in);
	DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in, double ro_in, double dt_in);
};

#endif