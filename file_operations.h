#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <chrono>
#include <cstring>
#include <filesystem>
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

class Catalog {
  public:
    Catalog(std::string filepath);
    int convertQuantaToInt(std::string &quanta);
	struct Line {
		double freq;
		double error;
		double logIntensity;
		int degFree;
		double lowEnergy;
		int upperDeg;
		int tag;
		int quantFmt;
		int quanta1;
		int quanta2;
		int quanta3;
		int quanta4;
		int quanta5;
		int quanta6;
        int quanta1Prime;
        int quanta2Prime;
        int quanta3Prime;
        int quanta4Prime;
        int quanta5Prime;
        int quanta6Prime;
	};
    const std::vector<Line> &getLines();
  private:
    std::vector<Line> lines;

};

#endif // !FILE_OPERATIONS_H
