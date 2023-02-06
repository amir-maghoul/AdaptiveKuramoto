#ifndef _DISCRETE_GRAPH_H_
#define _DISCRETE_GRAPH_H_

#include <eigen/Dense>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

/** Discrete Erdos Reyni Graph of probability p
*/
inline Eigen::MatrixXd DiscreteErdosReyniGraph(int size, double p){
    double win = p*100;
    double loss = (1-p)*100;
    std::random_device r;
    std::mt19937 m(r());
    std::discrete_distribution<> dist({loss, win});
    Eigen::MatrixXd M(size, size);
    for (size_t i=0; i<size;++i){
        for (size_t j=0; j<size;++j){
            M(i, j) = dist(m);
        }
    }
    return M;
}

#endif