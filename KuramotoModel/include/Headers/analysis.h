#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include "iofunctions.h"
#include <algorithm>
#include "continuous_extension.h"
#include "integral_solver.h"

std::vector<Eigen::MatrixXd> ConvertContinuousExtension(std::vector<Eigen::MatrixXd> VectorData,  int ReferenceN, bool isMatrix);

std::vector<std::string> CreateDiscreteFileAddressString(std::string ReadFileLoc, std::string GraphType, int n, double tend);

std::vector<std::string> CreateContlimFileAddressString(std::string ReadFileLoc, std::string GraphType, int ReferenceN, double tend);

std::vector<std::vector<Eigen::MatrixXd>> ReadDiscreteDataAndConvert(std::string ReadFileLoc, std::string GraphType, int n, int ReferenceN, double tend);

std::vector<std::vector<Eigen::MatrixXd>> ReadContlimData(std::string ReadFileLoc, std::string GraphType, int ReferenceN, double tend);

std::vector<double> WeightL1Error(std::vector<Eigen::MatrixXd> DiscreteMatrixVector, std::vector<Eigen::MatrixXd> ContlimMatrixVector);

std::vector<double> PhaseError(std::vector<Eigen::MatrixXd> DiscreteMatrixVector, std::vector<Eigen::MatrixXd> ContlimMatrixVector);

double TotalError(std::vector<std::vector<Eigen::MatrixXd>> DiscreteData, std::vector<std::vector<Eigen::MatrixXd>> ContlimData);

std::vector<double> SingleTimeAnalysis(std::vector<int> n, double tend, int ReferenceN, std::string GraphType, std::string ReadFileLoc);


#endif