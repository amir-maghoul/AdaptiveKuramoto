#include "include/Headers/analysis.h"

std::vector<Eigen::MatrixXd> ContinuousExtensionConverter(std::vector<Eigen::MatrixXd> VectorData, int ReferenceN, bool isMatrix){

    auto ContExt1D = [ReferenceN](Eigen::MatrixXd Matrix){
        return DiscretizedContinuousExtension1D(Matrix, ReferenceN);
    };

    auto ContExt2D = [ReferenceN](Eigen::MatrixXd Matrix){
        return DiscretizedContinuousExtension2D(Matrix, ReferenceN);
    };

    std::vector<Eigen::MatrixXd> result;

    if (isMatrix){
        std::transform(VectorData.begin(), VectorData.end(), result.begin(), ContExt2D);
    }else{
        std::transform(VectorData.begin(), VectorData.end(), result.begin(), ContExt1D);

    }
    return result;
}