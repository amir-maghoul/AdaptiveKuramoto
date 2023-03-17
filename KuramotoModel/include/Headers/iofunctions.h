#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include <fstream>
#include <eigen/Dense>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <filesystem>

inline std::vector<Eigen::MatrixXd> ReadData(std::string file_name, unsigned int n, bool isMatrix){
    std::vector<Eigen::MatrixXd> result;
    Eigen::VectorXd rowMatrix;

    if (isMatrix){
        rowMatrix.setZero(n*n);
    }else{
        rowMatrix.setZero(n);
    }
    std::fstream fin;
    fin.open(file_name, std::ios::in);
    std::string temp, line, word;
    while (fin >> line) {
        std::stringstream s(line);
        int i = 0;
        while (std::getline(s, word, ',')) {
            rowMatrix(i) = std::stod(word);
            i++;
        }
        if (isMatrix){
            result.push_back(rowMatrix.reshaped(n, n));
        }
        else{
            result.push_back(rowMatrix);
        }

    }
    
    return result;
}

inline void WriteError(std::string FileName, std::vector<double> Error){
    std::cout << "Writing error..." << std::endl;
    std::fstream File;
    File.open(FileName, std::ios_base::out);

    for (size_t i = 0; i < Error.size(); ++i)
    {
        File << Error.at(i) << ",";    
        File << "\n";
    } 
    File.close();

}

inline void WriteData(std::string file_name, std::vector<Eigen::MatrixXd> matrix)
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

inline void WriteVector(std::string file_name, std::vector<Eigen::MatrixXd> vector)
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