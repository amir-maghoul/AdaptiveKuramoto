#include <iostream>
#include "include/adaptive_kuramoto.h"
#include "include/abstract_kuramoto.h"
#include <Eigen/Dense>

using namespace std;

int main(int argc, char **argv)
{
	// Eigen::Vector3d w(28, 19, 11);
	Eigen::Matrix<double, 3, 1> w {28, 19, 11};
	Eigen::Matrix3d K0;
	K0 << 0, 	0.2, 	1.1,
		  0.5,	0,		-0.7,
		  0.3, 	0.9, 	0;


	AbstractModel *empty;
	std::cout << empty->w<< std::endl;

	AdaptiveKuramoto object{w, K0, 0.01, 0.3};
	std::cout << K0 << std::endl;

	Eigen::Matrix<double, 3, 1> v {28, 19, 11};
	std::cout << v << std::endl;

	// a = object.dynamics();




}
