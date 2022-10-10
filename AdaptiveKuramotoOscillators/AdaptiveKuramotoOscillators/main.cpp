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

	DiscreteKuramoto object{w, K0};
	cout << "[";
	for(int i=0;i<w.size();i++){
		cout << w[i] << " ";
		};
	cout << "]";
	cout << endl;
}
