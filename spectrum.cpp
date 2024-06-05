#include "spectrum.h"

std::tuple<std::vector<double>, std::vector<int>>
Spectrum::readBinarySpectrum(const std::string &filepath) {
	std::filesystem::path inputFilePath{filepath};
	auto length = std::filesystem::file_size(inputFilePath);
	if (length == 0) {
		return {};
	}
	std::vector<std::byte> buffer(length);
	std::ifstream inputFile(filepath, std::ios_base::binary);
	inputFile.read(reinterpret_cast<char *>(buffer.data()), length);
	inputFile.close();
	std::vector<std::byte> intensities_bytes(buffer.begin() + 162,
											 buffer.end() - 26);
	std::vector<std::byte> frequency_bytes(buffer.end() - 26, buffer.end() - 2);
	std::vector<int> intensities = bytesToInt(intensities_bytes);
	std::vector<double> frequency_doubles = bytesToDouble(frequency_bytes);
	std::vector<double> freqs = constructFreqs(frequency_doubles);
	return {freqs, intensities};
}

std::vector<int> Spectrum::bytesToInt(const std::vector<std::byte> &bytes)
/*
   Convert a vector of bytes to a vector of integers
   This data is stored as 16-bit (4-byte) integers in the binary file
*/
{
	std::vector<int> int_vector;
	char *ptr =
		const_cast<char *>(reinterpret_cast<const char *>(bytes.data()));
	for (int i = 0; i < bytes.size(); i += sizeof(int)) {
		int tmp;
		std::memcpy(&tmp, ptr + i, sizeof(int));
		int_vector.push_back(tmp);
	}
	return int_vector;
}

std::vector<double> Spectrum::bytesToDouble(const std::vector<std::byte> &bytes)
/*
   Convert a vector of bytes to a vector of doubles
   This data store the start freq, end freq, and increment.
*/
{
	std::vector<double> double_vector;
	char *ptr =
		const_cast<char *>(reinterpret_cast<const char *>(bytes.data()));
	for (int i = 0; i < bytes.size(); i += sizeof(double)) {
		double tmp;
		std::memcpy(&tmp, ptr + i, sizeof(double));
		double_vector.push_back(tmp);
	}
	return double_vector;
}

std::vector<double>
Spectrum::constructFreqs(const std::vector<double> &freq_data)
/*
   Convert a vector of bytes to a vector of doubles
   This data store the start freq, end freq, and increment.
*/
{
	std::vector<double> freqs;
	double freq_dif = freq_data[1] - freq_data[0];
	double freqi = freq_dif / freq_data[2];
	double tmp = freq_data[0];
	while (tmp < freq_data[1]) {
		freqs.push_back(tmp);
		tmp += freq_data[2];
	}
	return freqs;
}

Spectrum::Spectrum(std::string filepath) {
    std::tie(freqs, intensities) = readBinarySpectrum(filepath);
}

const std::vector<double> Spectrum::getFreqs() const {
    return freqs;
}
const std::vector<int> Spectrum::getIntensities() const {
    return intensities;
}

