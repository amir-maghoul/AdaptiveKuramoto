#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include <fstream>
#include <eigen/Dense>
#include <vector>
#include <iostream>

inline void write_data(std::string file_name, std::vector<Eigen::MatrixXd> matrix)
{
    std::cout << "Writing matrix..."<< std::endl;
    std::fstream file;
    file.open(file_name, std::ios_base::out);

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j=0; j < matrix.at(i).size(); ++j)
        {
            file << (matrix.at(i))(j) << ",";    
        }
        file << "\n";
    } 
    file.close();
}

inline void write_vector(std::string file_name, std::vector<double> vector)
{
    std::cout << "Writing vector..."<< std::endl;
    std::fstream file;
    file.open(file_name, std::ios_base::out);

    for (size_t i = 0; i < vector.size(); ++i)
    {
        file << vector.at(i) << ",";    
        file << "\n";
    } 
    file.close();
}

#endif