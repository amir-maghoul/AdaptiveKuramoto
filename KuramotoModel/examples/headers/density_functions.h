#ifndef _DENSITY_FUNCTIONS_H_
#define _DENSITY_FUNCTIONS_H_

#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <algorithm>

/**
*/
/* Weight Functions */

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

/** Erdos Reyni Graph of probability p
*/
inline double ErdosReyniGraph(double x, double y, double p){
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
    return 0.5*(1+cos(2*M_PI*(x-y)));
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

inline double RandomFunction(double x, int upper_bound){
    return rand()%upper_bound;
}

inline double SinFunction(double x){
    return sin(x);
}

inline double CosFunction(double x){
    return cos(x);
}

inline double ExpFunction(double x){
    return exp(x);
}

inline double NormalDistributionFunction(double x){
    return exp(-0.5*pow(x,2))/(sqrt(2*M_PI));
}

#endif