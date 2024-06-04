#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <cstring>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

class Spectrum {
  private:
	std::vector<int> intensities;
	std::vector<double> freqs;
	std::tuple<std::vector<int>, std::vector<double>>
	readBinarySpectrum(const std::string &filepath);
	std::vector<int> bytesToInt(const std::vector<std::byte> &bytes);
	std::vector<double> bytesToDouble(const std::vector<std::byte> &bytes);
	std::vector<double> constructFreqs(const std::vector<double> &freq_data);

  public:
	Spectrum(std::string filepath);
	const std::vector<int> &getIntensities();
	const std::vector<double> &getFreqs();
};

#endif // !SPECTRUM_H
