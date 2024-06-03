#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>
#include <numeric>

std::tuple<std::vector<int>, std::vector<double>> readBinarySpectrum(const std::string &filepath);
std::vector<int> bytesToInt(const std::vector<std::byte> &bytes);
std::vector<double> bytesToDouble(const std::vector<std::byte> &bytes);
std::vector<double> construct_freqs(const std::vector<double> &freq_data); 


#endif // !FILE_OPERATIONS_H
