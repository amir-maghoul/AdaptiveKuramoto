#ifndef _INTEGRATORS_H_
#define _INTEGRATORS_H_

#include <vector>
#include <eigen/Dense>
#include <iostream>


struct Integrator
{
    // Attributes
    double lower_bound;                     ///< Lower bound of intergration
    double upper_bound;                     ///< Upper bound of integration
    int d;                                  ///< Number of discretization points on the space
    int n;                                  ///< Dimensions of the space/function
    double h;                               ///< Delta x

    Integrator(double lower = 0, double upper = 1, int d_in = 50, int n_in = 1)
            : lower_bound{lower}, upper_bound{upper}, d{d_in}, n{n_in}, h{(upper_bound - lower_bound)/d}{};
    ~Integrator(){};


    /**
     * Discretized space and returns a vector of d discrete points in space
    */
    std::vector<double> DiscretizeSpace()
    {   
        std::vector<double> DiscreteSpace(d);
        for (size_t i=0; i < d; ++i)
        {
            DiscreteSpace[i] = i*h;
        };
        return DiscreteSpace;
    };

    /**
     * 1D Trapozoidal Rule
    */
   template<typename Function>
    double TrapozoidalRule1D(Function &&F)
    {
        std::vector<double> DiscreteSpace = DiscretizeSpace();
        double integral;
        for (size_t i=1; i < d; ++i)
        {
            integral += (h/2)*(F(DiscreteSpace[i])+F(DiscreteSpace[i-1]));
        };
        return integral;
    };

    /**
     * Integrates a 2D function in one variable.
     * The return value is a vector of summed (in the sense of trapozoidal rule) over rows or columns.
     * Each row or column of the output is the integrated value in one direction for a fixed value of 
     * another direction.
     * 
     * @param direction std::string. Values: "x" or "y". Specifier in which direction must be integrated
     * 
     * @return Eigen::VectorXd
    */
    template<typename Function>
    Eigen::VectorXd TrapozoidalRule1Din2D(Function &&F, const std::string &direction)
    {   
        Eigen::VectorXd INTEGRAL(d, 1);
        INTEGRAL.setZero();
        std::vector<double> DiscreteSpace = DiscretizeSpace();

        for (size_t i=0;i<d;++i)
        {
            for (size_t j=0;j<d;++j)
            {
                if (direction == "x"){
                    INTEGRAL[i] += (h/2)*(F(DiscreteSpace[i], DiscreteSpace[j])+F(DiscreteSpace[i], DiscreteSpace[j-1]));
                } 
                else if (direction == "y"){
                    INTEGRAL[i] += (h/2)*(F(DiscreteSpace[j], DiscreteSpace[i])+F(DiscreteSpace[j-1], DiscreteSpace[i]));
                }
            };
        };
        return INTEGRAL;
    };

    /**
     * Calculates the trapozoidal integral on a vector. The method used Eigen slicing for speed.
     * Assume the vector values at grid points are (f1, f2, f3, f4, f5).
     * Trapozoidal rule asserts the integral is (h/2)*sum(fi+fi+1). This corresponds to a vectorized operation
     * of two vectors v := (f1, f2, f3, f4) + (f2, f3, f4, f5) and then (h/2)*v.sum().
     * (f1, f2, f3, f4) = F(0:n-1) and (f2, f3, f4, f5) = F(1:n).
     * Therefore the integral would be (h/2)*(F(0:n-1) + F(1:n)).sum().
     * 
     * 
     * @param F Eigen::Vector the vector for the integral operand
     * 
     * @return double the integral value on the unit interval
    */
    double TrapozoidalRule1DMatrix(Eigen::VectorXd &F)
    {
        Eigen::VectorXd U(F.size()-1);
        U = F.segment(1, F.size()-1) + F.segment(0, F.size()-1);
        double integral;
        integral = (1.0/(double) 2*F.size())*U.sum();
        return integral;
    };

    /**
     * Calculates the integral in the given direction on a matrix function. Uses Eigen slicing for speed.
     * See the docs for TrapozoidalRule1DMatrix. 
     * Notice the direction is considered the array axis, not the mathematical coordinates.
     * This means direction == "x" is integration on the rows, not the x-axis in cartesian coordinates.
     * 
     * @param F Eigen::Matrix
     * @param direction string axis of integration
     * 
     * @return Eigen::Vector
    */
    Eigen::VectorXd TrapozoidalRuleIn2DMatrix(Eigen::MatrixXd &F, const std::string &direction)
    {
        long rows = F.rows();
        long cols = F.cols();
        Eigen::VectorXd INTEGRAL;

        if (direction == "x"){
            Eigen::MatrixXd U(rows, cols-1);
            U =F(Eigen::all, Eigen::seq(0,cols-2)) + F(Eigen::all, Eigen::seq(1,Eigen::last));
            INTEGRAL = U.rowwise().sum();
            INTEGRAL = (1.0/(double) (2*cols))*INTEGRAL;

        }
        else if (direction == "y"){
            Eigen::MatrixXd U(rows-1, cols);
            U =F(Eigen::seq(1,Eigen::last), Eigen::all) + F(Eigen::seq(0,rows-2), Eigen::all);
            INTEGRAL = U.colwise().sum();
            INTEGRAL = (1.0/(double) (2*rows))*INTEGRAL;

        }

        return INTEGRAL;
    };

    /**
     * Calculates the Simpson 3/8 rule integral on a vector. The method used Eigen slicing for speed.
     * Assume the vector values at grid points are (f1, f2, f3, f4, f5, f6, f7, f8).
     * See the formula in https://en.wikipedia.org/wiki/Simpson%27s_rule. 
     * This corresponds to a vectorized operation of  
     *      3*(0, f2, f3, f4, f5, f6, f7, 0) 
     *      - (0, 0, 0, f4, 0, 0, f7, 0) 
     *      + (f1, 0, 0, 0, 0, 0, 0, 0) 
     *      + (0, 0, 0, 0, 0, 0, f7, 0) 
     * 
     * and then (3*h/8)*v.sum().
     * 
     * 
     * @param F Eigen::Vector the vector for the integral operand
     * 
     * @return double the integral value on the unit interval
    */
    // double Simpsons3_8RuleVector(Eigen::VectorXd &F)
    // {
    //     double integral;
    //     integral = (3*F(Eigen::seq(1, Eigen::last))).sum() - F(Eigen::seq(3, Eigen::last, 3)).sum() + F(0) + F(Eigen::last);
    //     integral = (3.0/(double) 8*F.size())*integral;
    //     return integral;
    // };

    /**
     * Calculates the integral in the given direction on a matrix function using the Simpson's 3/8 rule. 
     * Uses Eigen slicing for speed.
     * See the docs for Simpsons3_8RuleVector. 
     * Notice the direction is considered the array axis, not the mathematical coordinates.
     * This means direction == "x" is integration on the rows, not the x-axis in cartesian coordinates.
     * 
     * @param M Eigen::Matrix
     * @param direction string axis of integration
     * 
     * @return Eigen::Vector
    */
    Eigen::VectorXd Simpsons3_8RuleIn2DMatrix(Eigen::MatrixXd &M, const std::string &direction){
        long rows = M.rows();
        long cols = M.cols();
        Eigen::VectorXd INTEGRAL;

        if (direction == "x"){
            Eigen::MatrixXd temp;
            temp = M(Eigen::all, Eigen::seq(3,Eigen::last,3));
            INTEGRAL = (3*M(Eigen::all, Eigen::seq(1,Eigen::last))).rowwise().sum() - temp.rowwise().sum()+ M(Eigen::all, 0) + M(Eigen::all, Eigen::last);
            INTEGRAL = (3.0/(double) (8*cols))*INTEGRAL;
        }
        else if (direction == "y"){
            Eigen::MatrixXd temp;
            temp = M(Eigen::seq(3,Eigen::last,3), Eigen::all);
            INTEGRAL =(3*M(Eigen::seq(1,Eigen::last), Eigen::all)).colwise().sum() - temp.colwise().sum() + M(0, Eigen::all) + M(Eigen::last, Eigen::all);
            INTEGRAL = (3.0/(double) (8*rows))*INTEGRAL;
        }

        return INTEGRAL;
    };

};

#endif