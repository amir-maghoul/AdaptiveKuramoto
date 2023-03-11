#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include <fstream>
#include <eigen/Dense>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

inline std::vector<Eigen::MatrixXd> read_data(std::string file_name, unsigned int n, bool isMatrix){
    std::vector<Eigen::MatrixXd> result;
    Eigen::VectorXd rowMatrix(n);

    std::fstream fin;
    fin.open(file_name, std::ios::in);
    std::string temp, line, word;
    while (fin >> line) {
        // std::cout << temp << std::endl;
        // std::getline(temp, line);
        std::stringstream s(line);
        // std::cout << line << std::endl;
        int i = 0;

        while (std::getline(s, word, ',')) {
            rowMatrix(i) = std::stod(word);
            i++;
        }
        result.push_back(rowMatrix);

    }
    
    return result;
}

inline void write_data(std::string file_name, std::vector<Eigen::MatrixXd> matrix)
{
    std::cout << "Writing matrix..."<< std::endl;
    std::fstream file;
    file.open(file_name, std::ios_base::out);

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j=0; j < matrix.at(i).size(); ++j)
        {
            file << std::setprecision(15) << (matrix.at(i))(j) << ",";    
        }
        file << "\n";
    } 
    file.close();
}

inline void write_vector(std::string file_name, std::vector<Eigen::MatrixXd> vector)
{
    std::cout << "Writing vector..."<< std::endl;
    std::fstream file;
    file.open(file_name, std::ios_base::out);

    for (size_t i = 0; i < vector.size(); ++i)
    {
        std::cout << vector.size() << std::endl;
        file << vector.at(i) << ",";    
        file << "\n";
    } 
    file.close();
}

#endif