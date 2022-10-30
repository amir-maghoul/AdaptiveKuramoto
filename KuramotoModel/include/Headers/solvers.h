#ifndef _SOLVERS_H_
#define _SOLVERS_H_


#include "runge_kutta.h"

namespace ExplicitRKSolvers{

    // Explicit Euler Method
    template <typename Function> 
    std::vector<Eigen::VectorXf> ExplicitEulerRule(Function f, const Eigen::VectorXf &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 10)
    {
        Eigen::MatrixXf B(1,1);             ///< Butcher Tableau slope matrix
        B << 0;
        
        Eigen::VectorXf C(1);               ///< Butcher Tableau coefficient matrix
        C << 1;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    }

    // Explicit Trapizoidal Rule
    template <typename Function> 
    std::vector<Eigen::VectorXf> ExplicitTrapezoidalRule(Function f, const Eigen::VectorXf &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 10)
    {
        Eigen::MatrixXf B(2,2);                ///< Butcher Tableau slope matrix
        B << 0, 0,
             1, 0;
        
        Eigen::VectorXf C(2);                  ///< Butcher Tableau coefficient matrix
        C << 0.5, 0.5;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Explicit Midpoint Rule
    template <typename Function>
    std::vector<Eigen::VectorXf> ExplicitMidPointRule(Function f, const Eigen::VectorXf &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 10)
    {
        Eigen::MatrixXf B(2,2);                 ///< Butcher Tableau slope matrix
        B << 0,   0,
             0.5, 0;
        
        Eigen::VectorXf C(2);                   ///< Butcher Tableau coefficient matrix
        C << 0, 1;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Classical 4th Order Runge Kutta
    template <typename Function>
    std::vector<Eigen::VectorXf> Explicit4thOrderRK(Function f, const Eigen::VectorXf &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 10)
    {
        Eigen::MatrixXf B(4, 4);                 ///< Butcher Tableau slope matrix   
        B << 0,     0,      0,      0,
             0.5,   0,      0,      0,
             0,     0.5,    0,      0,
             0,     0,      1,      0;
        
        Eigen::VectorXf C(4);
        C << 1.0/6, 2.0/6, 2.0/6, 1.0/6;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Runge Kutta's 3/8-Rule
    template <typename Function>
    std::vector<Eigen::VectorXf> RK38thRule(Function f, const Eigen::VectorXf &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 10)
    {
        Eigen::MatrixXf B(4,4);
        B << 0,         0,      0,      0,
             1.0/3,     0,      0,      0,
            -1.0/3,     1,      0,      0,
             1,        -1,      1,      0;
        
        Eigen::VectorXf C(4);
        C << 1.0/8, 3.0/8, 3.0/8, 1.0/8;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, 10);

    };

};
#endif
