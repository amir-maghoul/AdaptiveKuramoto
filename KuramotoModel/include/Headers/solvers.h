#ifndef _SOLVERS_H_
#define _SOLVERS_H_


#include "runge_kutta.h"


namespace ExplicitRKSolvers{

    // Explicit Euler Method
    template <typename Function> 
    std::vector<Eigen::VectorXd> ExplicitEulerRule(Function f, const Eigen::VectorXd &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 11)
    {
        Eigen::MatrixXd B(1,1);             ///< Butcher Tableau slope matrix
        B << 0;
        
        Eigen::VectorXd C(1);               ///< Butcher Tableau coefficient matrix
        C << 1;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    }

    // Explicit Trapizoidal Rule
    template <typename Function> 
    std::vector<Eigen::VectorXd> ExplicitTrapezoidalRule(Function f, const Eigen::VectorXd &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 11)
    {
        Eigen::MatrixXd B(2,2);                ///< Butcher Tableau slope matrix
        B << 0, 0,
             1, 0;
        
        Eigen::VectorXd C(2);                  ///< Butcher Tableau coefficient matrix
        C << 0.5, 0.5;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Explicit Midpoint Rule
    template <typename Function>
    std::vector<Eigen::VectorXd> ExplicitMidPointRule(Function f, const Eigen::VectorXd &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 11)
    {
        Eigen::MatrixXd B(2,2);                 ///< Butcher Tableau slope matrix
        B << 0,   0,
             0.5, 0;
        
        Eigen::VectorXd C(2);                   ///< Butcher Tableau coefficient matrix
        C << 0, 1;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Classical 4th Order Runge Kutta
    template <typename Function>
    std::vector<Eigen::VectorXd> Explicit4thOrderRK(Function f, const Eigen::VectorXd &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 11)
    {
        Eigen::MatrixXd B(4, 4);                 ///< Butcher Tableau slope matrix   
        B << 0,     0,      0,      0,
             0.5,   0,      0,      0,
             0,     0.5,    0,      0,
             0,     0,      1,      0;
        
        Eigen::VectorXd C(4);
        C << 1.0/6, 2.0/6, 2.0/6, 1.0/6;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, jump);

    };

    // Runge Kutta's 3/8-Rule
    template <typename Function>
    std::vector<Eigen::VectorXd> RK38thRule(Function f, const Eigen::VectorXd &X0, unsigned int num_steps, float t0=0, float tend=1, unsigned int jump = 11)
    {
        Eigen::MatrixXd B(4,4);
        B << 0,         0,      0,      0,
             1.0/3,     0,      0,      0,
            -1.0/3,     1,      0,      0,
             1,        -1,      1,      0;
        
        Eigen::VectorXd C(4);
        C << 1.0/8, 3.0/8, 3.0/8, 1.0/8;

        ExplicitRungeKutta ERK(B, C, num_steps, t0, tend);
        return ERK.solve(f, X0, 10);

    };

};
#endif
