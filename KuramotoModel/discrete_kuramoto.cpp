#include "discrete_kuramoto.h"
#include <iostream>

DiscreteKuramoto::DiscreteKuramoto(){};
DiscreteKuramoto::DiscreteKuramoto(std::vector<double> w_in, 
								   std::vector<std::vector<double>> K0_in, 
								   double ro_in, 
								   double t0_in,
								   double t_end_in,
								   double epsilon_in,
								   double dt_in)
	:	w{w_in}, K0{K0_in}, ro{ro_in}, t0{t0_in}, t_end{t_end_in}, epsilon{epsilon_in}, dt{dt_in}{
};

DiscreteKuramoto::~DiscreteKuramoto(){
	std::cout << "The class destructor was called for DiscreteKuramoto." << std::endl;
	};