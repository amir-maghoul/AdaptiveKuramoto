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
    ~Integrator(){std::cout << "Descructor of Integrator class was called" << std::endl;};


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
        Eigen::VectorXd integral(d, 1);
        integral.setZero();
        std::vector<double> DiscreteSpace = DiscretizeSpace();

        for (size_t i=0;i<d;++i)
        {
            for (size_t j=0;j<d;++j)
            {
                if (direction == "x"){
                    integral[i] += (h/2)*(F(DiscreteSpace[i], DiscreteSpace[j])+F(DiscreteSpace[i], DiscreteSpace[j-1]));
                } 
                else if (direction == "y"){
                    integral[i] += (h/2)*(F(DiscreteSpace[j], DiscreteSpace[i])+F(DiscreteSpace[j-1], DiscreteSpace[i]));
                }
            };
        };
        return integral;
    };

};

#endif