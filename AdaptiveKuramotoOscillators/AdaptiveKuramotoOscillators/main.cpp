#include <iostream>
#include "discrete_kuramoto.h"
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	vector<double> w = {28, 19, 11};
	vector<vector<double>> K0
	{
		{0, 0.2, 1.1},
		{0.5, 0, -0.7},
		{0.3, 0.9, 0}

	};
	DiscreteKuramoto empty;

	DiscreteKuramoto object{w, K0, 0.01, 0.3};
	w = {20, 11, 10};
	object.w = w;


}
