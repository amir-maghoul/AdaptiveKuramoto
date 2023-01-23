#ifndef _FUNCTION_INTEGRATOR_H_
#define _FUNCTION_INTEGRATOR_H_

#include "integrators.h"

namespace IntegralSolvers{

    template<typename Function>
    double Trap1D(Function &M, double lower_bound, double upper_bound, int d, int n){
        
        Integrator INT(lower_bound, upper_bound, d, n);
        return INT.TrapozoidalRule1D(M);
    }

    inline Eigen::VectorXd TrapMatrixin1D(Eigen::MatrixXd &M, double lower_bound, double upper_bound, int d, int n, const std::string &direction){

        Integrator INT(lower_bound, upper_bound, d, n);
        return INT.TrapozoidalRuleIn2DMatrix(M, direction);

    };

    inline Eigen::VectorXd SimpsonMatrix1D(Eigen::MatrixXd &M, double lower_bound, double upper_bound, int d, int n, const std::string &direction){

        Integrator INT(lower_bound, upper_bound, d, n);
        return INT.Simpsons3_8RuleIn2DMatrix(M, direction);
    };

};

#endif