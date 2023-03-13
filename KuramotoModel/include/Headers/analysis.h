#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include "iofunctions.h"
#include <algorithm>
#include "continuous_extension.h"
#include "integral_solver.h"

std::vector<Eigen::MatrixXd> ContinuousExtensionConverter(std::vector<Eigen::MatrixXd> VectorData,  int ReferenceN, bool isMatrix);
void ReadConvertWrite(std::string ReadFileLoc, std::string WriteFileLoc, std::string GraphType, int n, int ReferenceN, bool isMatrix, double tend);
std::vector<double> WeightL1Error(std::vector<Eigen::MatrixXd> DiscreteMatrix, std::vector<Eigen::MatrixXd> ContlimMatrix);

#endif