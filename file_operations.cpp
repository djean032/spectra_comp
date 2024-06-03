#include "file_operations.h"

std::tuple<std::vector<int>, std::vector<double>>
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
	return {intensities, freqs};
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
	std::tie(intensities, freqs) = readBinarySpectrum(filepath);
}

const std::vector<int> &Spectrum::getIntensities() { return intensities; }

const std::vector<double> &Spectrum::getFreqs() { return freqs; }

// Catalog Class stuff

Catalog::Catalog(std::string filepath) {
	std::vector<Line> catalogLines;
	std::ifstream inputFile(filepath);
	std::string line;
	while (std::getline(inputFile, line)) {
		Line l;
        std::string quanta1, quanta2, quanta3, quanta4, quanta5, quanta6;
        std::string quanta1Prime, quanta2Prime, quanta3Prime, quanta4Prime, quanta5Prime, quanta6Prime;
		l.freq = std::stod(line.substr(0, 13));
		l.error = std::stod(line.substr(13, 8));
		l.logIntensity = std::stod(line.substr(21, 8));
		l.degFree = std::stoi(line.substr(29, 2));
		l.lowEnergy = std::stod(line.substr(31, 10));
		l.upperDeg = std::stoi(line.substr(41, 3));
		l.tag = std::stoi(line.substr(44, 7));
        l.quantFmt = std::stoi(line.substr(51, 4));
        quanta1 = line.substr(55, 2);
        quanta2 = line.substr(57, 2);
        quanta3 = line.substr(59, 2);
        quanta4 = line.substr(61, 2);
        quanta5 = line.substr(63, 2);
        quanta6 = line.substr(65, 2);
        quanta1Prime = line.substr(67, 2);
        quanta2Prime = line.substr(69, 2);
        quanta3Prime = line.substr(71, 2);
        quanta4Prime = line.substr(73, 2);
        quanta5Prime = line.substr(75, 2);
        quanta6Prime = line.substr(77, 2);
        if (l.quantFmt / 100 == 14) {
            l.quanta1 = convertQuantaToInt(quanta1);
            l.quanta2 = convertQuantaToInt(quanta2);
            l.quanta3 = convertQuantaToInt(quanta3);
            l.quanta4 = convertQuantaToInt(quanta4);
            l.quanta5 = 0;
            l.quanta6 = 0;
            l.quanta1Prime = convertQuantaToInt(quanta1Prime);
            l.quanta2Prime = convertQuantaToInt(quanta2Prime);
            l.quanta3Prime = convertQuantaToInt(quanta3Prime);
            l.quanta4Prime = convertQuantaToInt(quanta4Prime);
            l.quanta5Prime = 0;
            l.quanta6Prime = 0;
        } else {
            std::cout << "Quantum format not supported" << std::endl;
        }

		lines.push_back(l);
	}
}

const std::vector<Catalog::Line> &Catalog::getLines() { return lines; }

int Catalog::convertQuantaToInt(std::string &quanta) {
	char first_letter = quanta.at(0);
	int tmp{0};
	if (isalpha(first_letter)) {
		for (auto &c : quanta) {
			if (isupper(c)) {
				tmp += 10 * ((int)c - 55);
			} else if (islower(c)) {
				tmp += -10 * ((int)c - 96);
			} else {
				tmp += (int)c - '0';
			}
		}
	} else {
		return std::stoi(quanta);
	}
	return tmp;
}
