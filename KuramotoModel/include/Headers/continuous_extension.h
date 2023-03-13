#ifndef _CONTINUOUS_EXTENSION_H_
#define _CONTINUOUS_EXTENSION_H_

#include <vector>
#include <eigen/Dense>
#include <iostream>
#include "include/Headers/iofunctions.h"

Eigen::MatrixXd DiscretizedContinuousExtension1D(Eigen::VectorXd Matrix, int N);
Eigen::MatrixXd DiscretizedContinuousExtension2D(Eigen::MatrixXd Matrix, int N);


#endif