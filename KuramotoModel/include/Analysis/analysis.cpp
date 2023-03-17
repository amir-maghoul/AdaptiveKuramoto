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
std::vector<Eigen::MatrixXd> ConvertContinuousExtension(std::vector<Eigen::MatrixXd> VectorData, int ReferenceN, bool isMatrix){

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

std::vector<double> PhaseInfError(std::vector<Eigen::MatrixXd> DiscreteMatrixVector, std::vector<Eigen::MatrixXd> ContlimMatrixVector){
    
    int size = DiscreteMatrixVector.at(0).rows();
    std::vector<double> Error(DiscreteMatrixVector.size());

    for (size_t i=0; i<Error.size();++i){
            Error[i] = ((DiscreteMatrixVector.at(i) - ContlimMatrixVector.at(i)).cwiseAbs()).maxCoeff();    
    };

    return Error;
}

double TotalError(std::vector<std::vector<Eigen::MatrixXd>> DiscreteData, std::vector<std::vector<Eigen::MatrixXd>> ContlimData){
    
    std::vector<double> WeightError(DiscreteData.at(0).size());
    std::vector<double> PhaseError(DiscreteData.at(0).size());
    std::vector<double> TotalError(DiscreteData.at(0).size());

    WeightError = WeightL1Error(DiscreteData.at(0), ContlimData.at(0));
    PhaseError = PhaseInfError(DiscreteData.at(1), ContlimData.at(1));
    std::transform(WeightError.begin(), WeightError.end(), PhaseError.begin(), TotalError.begin(), std::plus<double>());

    return *std::max_element(TotalError.begin(), TotalError.end());

}

std::vector<std::string> CreateDiscreteFileAddressString(std::string ReadFileLoc, std::string GraphType, int n, double tend){
    std::string DiscreteSignatureName = "contlim_" + GraphType + "_with_" + std::to_string(n) + "_oscillators_";
    std::string DiscreteWeightsFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + DiscreteSignatureName + "tend_" +std::to_string((int) tend) + ".txt";
    std::string DiscretePhasesFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + DiscreteSignatureName + "phases_tend_" +std::to_string((int) tend) + ".txt";

    std::vector<std::string> result {DiscreteWeightsFileName, DiscretePhasesFileName};
    return result;
}

std::vector<std::string> CreateContlimFileAddressString(std::string ReadFileLoc, std::string GraphType, int ReferenceN, double tend){
    std::string ContLimSignatureName = "contlim_" + GraphType + "_with_" + std::to_string(ReferenceN) + "_oscillators_";
    std::string ContlimWeightsFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + ContLimSignatureName + "tend_" +std::to_string((int) tend) + ".txt";
    std::string ContlimPhasesFileName = ReadFileLoc + "tend_" + std::to_string((int) tend) + "/" + ContLimSignatureName + "phases_tend_" +std::to_string((int) tend) + ".txt";

    std::vector<std::string> result {ContlimWeightsFileName, ContlimPhasesFileName};

    return result;
}

std::vector<std::vector<Eigen::MatrixXd>> ReadDiscreteDataAndConvert(std::string ReadFileLoc, std::string GraphType, int n, int ReferenceN, double tend){
    
    std::vector<std::string> FileAddresses(2);
    FileAddresses = CreateDiscreteFileAddressString(ReadFileLoc, GraphType, n, tend);

    std::vector<Eigen::MatrixXd> DiscreteWeightMatrix = ReadData(FileAddresses.at(0), n, true);
    std::vector<Eigen::MatrixXd> DiscretePhaseMatrix = ReadData(FileAddresses.at(1), n, false);

    DiscreteWeightMatrix = ConvertContinuousExtension(DiscreteWeightMatrix, ReferenceN, true);
    DiscretePhaseMatrix = ConvertContinuousExtension(DiscretePhaseMatrix, ReferenceN, false);

    std::vector<std::vector<Eigen::MatrixXd>> result {DiscreteWeightMatrix, DiscretePhaseMatrix};

    return result;

};

std::vector<std::vector<Eigen::MatrixXd>> ReadContlimData(std::string ReadFileLoc, std::string GraphType, int ReferenceN, double tend){
    
    std::vector<std::string> FileAddresses(2);
    FileAddresses = CreateContlimFileAddressString(ReadFileLoc, GraphType, ReferenceN, tend);

    std::vector<Eigen::MatrixXd> ContlimWeightMatrix = ReadData(FileAddresses.at(0), ReferenceN, true);
    std::vector<Eigen::MatrixXd> ContlimPhaseMatrix = ReadData(FileAddresses.at(1), ReferenceN, false);

    std::vector<std::vector<Eigen::MatrixXd>> result {ContlimWeightMatrix, ContlimPhaseMatrix};

    return result;

};
std::vector<double> SingleTimeAnalysis(std::vector<int> n, double tend, int ReferenceN, std::string GraphType, std::string ReadFileLoc){
    
    
    std::vector<std::vector<Eigen::MatrixXd>> ContlimData(2);
    ContlimData = ReadContlimData(ReadFileLoc, GraphType, ReferenceN, tend);

    std::vector<double> Error(n.size());

    std::vector<std::vector<Eigen::MatrixXd>> DiscreteData(2);
    for (size_t i=0; i<n.size();++i){
        std::cout << "n = " << n.at(i) << std::endl;
        DiscreteData = ReadDiscreteDataAndConvert(ReadFileLoc, GraphType, n.at(i), ReferenceN, tend);
        Error[i] = TotalError(DiscreteData, ContlimData);
    };

    std::string WriteFileLoc = ReadFileLoc + "Errors/" + "tend_" + std::to_string((int) tend) + "/";
    std::string WriteFileName = "error_with_reference_" + std::to_string(ReferenceN) + ".txt";

    std::filesystem::create_directories(WriteFileLoc);


    WriteError(WriteFileLoc + WriteFileName, Error);



    return Error;
};