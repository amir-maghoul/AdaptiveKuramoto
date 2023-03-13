#include "include/Headers/analysis.h"

/**
 * Convert a std::vector of matrices into a std::vector of matrices which are discretized continuous
 * extension of the original matrices.
 * 
 * @param VectorData        std::vector<Eigen::MatrixXd>     The input vector of matrices to be converted
 * @param ReferenceN        int     The number of discretization point after continuous extension
 * @param isMatrix          bool    Boolean flag to check if the vector contains 1D or 2D matrices
 * 
 * @return  std::vector<Eigen::MatrixXd> The new vector of discretized continuously extended matrices
 * 
*/
std::vector<Eigen::MatrixXd> ContinuousExtensionConverter(std::vector<Eigen::MatrixXd> VectorData, int ReferenceN, bool isMatrix){

    auto ContExt1D = [ReferenceN](Eigen::MatrixXd Matrix){
        return DiscretizedContinuousExtension1D(Matrix, ReferenceN);
    };

    auto ContExt2D = [ReferenceN](Eigen::MatrixXd Matrix){
        return DiscretizedContinuousExtension2D(Matrix, ReferenceN);
    };

    std::vector<Eigen::MatrixXd> result(VectorData.size());

    if (isMatrix){
        std::transform(VectorData.begin(), VectorData.end(), result.begin(), ContExt2D);
    }else{
        std::transform(VectorData.begin(), VectorData.end(), result.begin(), ContExt1D);

    }
    return result;
}

std::vector<double> WeightL1Error(std::vector<Eigen::MatrixXd> DiscreteMatrixVector, std::vector<Eigen::MatrixXd> ContlimMatrixVector){
    int size = DiscreteMatrixVector.at(0).rows();
    std::vector<double> Error(DiscreteMatrixVector.size());

    auto TrapozoidSolver = [size](Eigen::MatrixXd M){
        return IntegralSolvers::TrapMatrixin1D(M, 0, 1, size, 1, "x");
    };

    for (size_t i=0; i<Error.size();++i){
            Error[i] = TrapozoidSolver((DiscreteMatrixVector.at(i) - ContlimMatrixVector.at(i)).cwiseAbs()).maxCoeff();    
    };
    return Error;
}

std::vector<double> PhaseError(std::vector<Eigen::MatrixXd> DiscreteMatrixVector, std::vector<Eigen::MatrixXd> ContlimMatrixVector){
    int size = DiscreteMatrixVector.at(0).rows();
    std::vector<double> Error(DiscreteMatrixVector.size());

    for (size_t i=0; i<Error.size();++i){
            Error[i] = ((DiscreteMatrixVector.at(i) - ContlimMatrixVector.at(i)).cwiseAbs()).maxCoeff();    
    };
    return Error;
}


void ReadConvertWrite(std::string ReadFileLoc, std::string WriteFileLoc, std::string GraphType, int n, int ReferenceN, bool isMatrix, double tend){
    std::string ContLimSignatureName = "contlim_" + GraphType + "_with_" + std::to_string(ReferenceN) + "_oscillators_";
    std::string DiscreteSignatureName = "discrete_" + GraphType + "_with_" + std::to_string(n) + "_oscillators_";

    std::string ContlimWeightsFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + ContLimSignatureName + "tend_" +std::to_string((int) tend) + ".txt";
    std::string DiscreteWeightsFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + DiscreteSignatureName + "tend_" +std::to_string((int) tend) + ".txt";

    std::string ContlimPhasesFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + ContLimSignatureName + "phases_tend_" +std::to_string((int) tend) + ".txt";
    std::string DiscretePhasesFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + DiscreteSignatureName + "phases_tend_" +std::to_string((int) tend) + ".txt";

    std::cout << ContlimWeightsFileName << std::endl;
    std::cout << DiscreteWeightsFileName << std::endl;
    std::cout << ContlimPhasesFileName << std::endl;
    std::cout << DiscretePhasesFileName << std::endl;


}