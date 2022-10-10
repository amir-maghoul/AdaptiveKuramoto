#include "discrete_kuramoto.h"

DiscreteKuramoto::DiscreteKuramoto(){};

DiscreteKuramoto::DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in){
	N			= w_in.size();
	w  			= w_in;
	K0 			= K0_in;
	ro 			= 0.2;
	t0			= 0;
	t_end 		= 40;
	epsilon 	= 0.01;
	dt			= 0.01;
};

DiscreteKuramoto::DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in, double ro_in){
	N			= w_in.size();
	w  			= w_in;
	K0 			= K0_in;
	ro 			= ro_in;
	t0			= 0;
	t_end 		= 40;
	epsilon 	= 0.01;
	dt			= 0.01;
};

DiscreteKuramoto::DiscreteKuramoto(std::vector<double> w_in, std::vector<std::vector<double>> K0_in, double ro_in, double dt_in){
	N			= w_in.size();
	w  			= w_in;
	K0 			= K0_in;
	ro 			= ro_in;
	t0			= 0;
	t_end 		= 40;
	epsilon 	= 0.01;
	dt 			= dt_in;
};
