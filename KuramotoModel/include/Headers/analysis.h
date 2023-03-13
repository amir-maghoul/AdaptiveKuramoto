#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include "iofunctions.h"
#include <algorithm>
#include "continuous_extension.h"

std::vector<Eigen::MatrixXd> ContinuousExtensionConverter(std::vector<Eigen::MatrixXd> VectorData,  int ReferenceN, bool isMatrix);


#endif