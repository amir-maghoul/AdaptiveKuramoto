/* This module has been written to compensate low performance of error analysis in Python. To my surprise though, this 
was slower than Python counterpart. My guess is that I still dont know the background operations of Eigen library
which make this slow. The newer Python algorithm is actually super fast. So I recommend using the Python code. 
I have uploaded this just in case for some user if the need arises. I will try to implement the same Python algorithm
here later, to be able to compare them.*/


#include <include/Headers/continuous_extension.h>

/* PLEASE READ THE MODULE COMMENTS ABOVE FIRST */
/***********************************************/

/**
 * Calculate the discretized continuous extension of a given 1D vector over the inteval [0, 1].
 * The function first assumes the continuous extension of the given vector over the interval, 
 * then discretizes the result. The continuous extension is the step function over the interval.
 * This means for example, the continuous extension of the vector v = [1, 2, 3] over the interal, first
 * discretizes the interval into 4 points (v.size() + 1) and assumes the corresponding element of v for
 * each subinterval, i.e. for the sub-interval [0, 0.333) the value of the continuous extension is v[1],
 * for the sub-interval [0.333, 0.666) the value is v[2] and so on. We call this first discretization
 * of the interval t1.
 * The discretization of the continuoous extension for a given N is done in a vectorized manner:
 * A copy of interval [0, 1] is discretized a second time into N points. We call this second discretization t.
 * For each point pt_ in t, we look for sub-intervals in t1 on which pt_ land in, and since we know the resulting
 * value for each sub-interval, we obtain the value for each pt_ and therefore for the whole t.
 * 
 * 
 * @param Matrix Eigen::VectorXd The vector which we want to continuously extend
 * @param N      int The discretization fineness after the extension
 * 
 * @return Eigen::MatrixXd A vector of size N as the continous extension of Matrix
 * 
*/

Eigen::MatrixXd DiscretizedContinuousExtension1D(Eigen::VectorXd Matrix, int N){

    const int n = Matrix.size();

    Eigen::VectorXd t1 = Eigen::VectorXd::LinSpaced(n+1, 0.0, 1.0);                         ///< First subdivision of the interval [0, 1]
    Eigen::VectorXd t = Eigen::VectorXd::LinSpaced(N, 0.0, 1.0);                            ///< Second subdivision of the interval

    Eigen::VectorXd result(N);                                                              ///< Initialization of the result as zeros
    result.setZero();                                                                       ///< Initialization of the result as zeros


    for (size_t i=1; i < t1.size();++i){
        result = (t.array() < t1[i] && t.array() >= t1[i-1]).select(Matrix(i-1), result);   ///< Find sub-intervals in t1 on which each element of t
    }                                                                                       ///< lands.
    result(N-1) = Matrix(n-1);                                                              ///< The last element is left out in the for loop. Fill for the last element.

    return result;
}


/**
 * Calculate the discretized continuous extension of a given 1D vector over the inteval [0, 1].
 * This is basically the same logic as DiscretizedContinuousExtension1D extended to 2D.
 * For this, we use the mesh grid created from the discretized interval.
 * For more details see the docs on the aforementioned function.
 * 
 * 
 * @param Matrix Eigen::MatrixXd The vector which we want to continuously extend
 * @param N      int The discretization fineness after the extension
 * 
 * @return Eigen::MatrixXd A Matrix of size NxN as the continous extension of Matrix
 * 
*/
Eigen::MatrixXd DiscretizedContinuousExtension2D(Eigen::MatrixXd Matrix, int N){

    const int n = Matrix.rows();
    Eigen::VectorXd t1 = Eigen::VectorXd::LinSpaced(n+1, 0.0, 1.0);                         ///< First subdivision of the interval [0, 1]
    Eigen::VectorXd t = Eigen::VectorXd::LinSpaced(N, 0.0, 1.0);                            ///< Second subdivision of the interval

    // Meshgrid matrices
    Eigen::MatrixXd XX = t.replicate(1, N).transpose();                                     ///< Meshgrid x values from discretized interval
    Eigen::MatrixXd YY = t.replicate(1, N);                                                 ///< Meshgrid y values from discretized interval

    // Initialize the result
    Eigen::MatrixXd result(N,N);
    result.setZero();

    const int rows = result.rows();
    const int cols = result.cols();

    // Logical indexing matrices
    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> idx1;                               ///< Initializing the logical indexing matrices
    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> idx2;
    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> idx;


    for (size_t i=1; i<t1.size();++i){
        for (size_t j=1; j<t1.size();++j){
            idx1 = (XX.array() < t1[i] && XX.array() >= t1[i-1]);                           ///< Find sub-intervals on which each element of t in XX lands.
            idx2 = (YY.array() < t1[j] && YY.array() >= t1[j-1]);                           ///< Find sub-intervals on which each element of t in YY lands.
            // logical AND of indices
            idx.noalias() = idx1.cwiseProduct(idx2);                                                  ///< Find the intersection of subintervals by logical AND of both indices.

            result = (idx).select(Matrix(j-1, i-1), result);
        }
    }
    result(Eigen::all, Eigen::last) = result(Eigen::all, Eigen::last-1);                    ///< Last rows and columns get left out from the for loop. 
    result(Eigen::last,Eigen::all) = result(Eigen::last-1, Eigen::all);                     ///< Fill for missing data

    return result;

}

