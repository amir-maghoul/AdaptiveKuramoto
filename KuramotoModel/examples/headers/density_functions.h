#ifndef _DENSITY_FUNCTIONS_H_
#define _DENSITY_FUNCTIONS_H_

#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

/**
*/
/* Weight Functions */

/** Fully Random Graph 
*/
inline double RandomGraph(double x, double y, double low, double high){
    std::random_device r;
    std::mt19937 m(r());
    std::uniform_real_distribution<double> dist(low, high);
    return dist(m);
}

/** Ring lattice of valid distance h
*/
inline double RingLatticeGraph(double x, double y, double h){
    if (std::min(abs(x - y), (1 - abs(x - y))) <= h){
        return 1;
    } 
    else{
        return 0;
    }
};

/** Continuous Erdos Reyni Graph of probability p
*/
inline double ContinuousErdosReyniGraph(double x, double y, double p){
    return p;
}

/** Small World Graph of probabilty p and valid distance h
*/
inline double SmallWorldGraph(double x, double y, double h, double p){
    return (1-p)*RingLatticeGraph(x, y, h) + 2*p*h;
}

/** Sinusoidal Graph
*/
inline double SinusoidalGraph(double x, double y){
    return 0.5*(1+cos(2*M_PI*(x-y))) + 0.5;
}

/** Sinus graph for stationary solution*/
inline double SinusGraph(double x, double y, double b, double k){
    // return -sin(k*M_PI*(x - y + b));
    return x - y;
}

/*
*/
/* Phase and Frequency Densities*/

inline double ZeroFunction(double x){
    return 0;
}

inline double ConstantFunction(double x, double constant_value){
    return constant_value;
}

inline double RandomFunction(double x, double low, double high){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(low, high);
    return dist(mt);
}

inline double SinFunction(double x){
    return sin(x*M_PI);
}

inline double CosFunction(double x){
    return cos(x*M_PI);
}

inline double ExpFunction(double x){
    return exp(x);
}

inline double NormalDistributionFunction(double x){
    return exp(-0.5*pow(x-0.5,2))/(sqrt(2*M_PI));
}

inline double PhiTilde(double x){
    return M_PI*x;
}

#endif