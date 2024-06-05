#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Spectrum {
  public:
	Spectrum(std::string filepath);
    const std::vector<double> getFreqs() const;
    const std::vector<int> getIntensities() const;

  private:
    std::tuple<std::vector<double>, std::vector<int>>
	readBinarySpectrum(const std::string &filepath);
	std::vector<int> bytesToInt(const std::vector<std::byte> &bytes);
	std::vector<double> bytesToDouble(const std::vector<std::byte> &bytes);
	std::vector<double> constructFreqs(const std::vector<double> &freq_data);
    std::vector<double> freqs;
    std::vector<int> intensities;
};

#endif // !SPECTRUM_H
