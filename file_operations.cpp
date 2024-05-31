#include "file_operations.h"
#include <algorithm>

std::vector<std::byte> readBinaryFile(const std::string &filepath);
std::vector<int> bytesToInt(const std::vector<std::byte> &bytes);
std::vector<double> bytesToDouble(const std::vector<std::byte> &bytes);
std::vector<double> construct_freqs(const std::vector<double> &freq_data); 

int main(int argc, char *argv[]) {

    auto begin = std::chrono::high_resolution_clock::now();
	std::vector<std::byte> buffer = readBinaryFile(
		R"(/home/dairen/Projects/rotspec_tools/cyanomethylenecyclopropane_235-500GHz_bin.spe)");
	std::vector<std::byte> intensities_bytes(buffer.begin() + 162,
											 buffer.end() - 26);
    std::vector<std::byte> frequency_bytes(buffer.end() - 26 , buffer.end() - 2);

	std::vector<int> intensities = bytesToInt(intensities_bytes);
    std::vector<double> frequency_doubles = bytesToDouble(frequency_bytes);
    std::vector<double> freqs = construct_freqs(frequency_doubles);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = end - begin;
    std::cout << "Elapsed time: " << elapsed_seconds.count() / 1e9 << "s\n";
	std::cout << intensities.size() << std::endl;
    std::cout << freqs.size() << std::endl;
    std::cout << freqs.back() << std::endl;
	return 0;
}

std::vector<std::byte> readBinaryFile(const std::string &filepath) {
	std::filesystem::path inputFilePath{filepath};
	auto length = std::filesystem::file_size(inputFilePath);
	if (length == 0) {
		return {};
	}
	std::vector<std::byte> buffer(length);
	std::ifstream inputFile(filepath, std::ios_base::binary);
	inputFile.read(reinterpret_cast<char *>(buffer.data()), length);
	inputFile.close();
	return buffer;
}

std::vector<int> bytesToInt(const std::vector<std::byte> &bytes) {
	std::vector<int> int_vector;
    char *ptr = const_cast<char*>(reinterpret_cast<const char*>(bytes.data()));
	for (int i = 0; i < bytes.size(); i+=sizeof(int)) {
        int tmp;
        std::memcpy(&tmp, ptr + i, sizeof(int));
        int_vector.push_back(tmp);
	}
	return int_vector;
}


std::vector<double> bytesToDouble(const std::vector<std::byte> &bytes) {
    std::vector<double> double_vector;
    char* ptr = const_cast<char*>(reinterpret_cast<const char*>(bytes.data()));
    for (int i = 0; i < bytes.size(); i+=sizeof(double)) {
        double tmp;
        std::memcpy(&tmp, ptr + i, sizeof(double));
        double_vector.push_back(tmp);
    }
    return double_vector;
}

std::vector<double> construct_freqs(const std::vector<double> &freq_data) {
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
/*
def read_spectra(filepath: str) -> dict:
	data = Path(filepath).read_bytes()
	# c = unpack("72s", data[0:72])[0]
	# iday, imon, iyear = unpack("3h", data[72:78])
	# ihour, imin, isec = unpack("3h", data[78:84])
	# lamp = unpack("6s", data[84:90])[0]
	# vkmst, vkmend = unpack("2f", data[90:98])
	# grid = unpack("f", data[98:102])[0]
	# sample = unpack("20s", data[102:122])[0]
	# sampre = unpack("f", data[122:126])[0]
	# gain, timec, phase = unpack("3f", data[126:138])
	# scansp = unpack("6s", data[138:144])[0]
	# pps = unpack("f", data[144:148])[0]
	# frmod, frampl = unpack("2f", data[148:156])
	# neg1 = unpack("h", data[156:158])[0]
	npts = abs(unpack("i", data[158:162])[0])
	ipsec_string = str(npts) + "i"
	ipsec = unpack(ipsec_string, data[162 : 162 + npts * 4])
	fstart, fend, fincr = unpack("3d", data[162 + npts * 4 : 162 + npts * 4 +
24]) freq_list = np.linspace(fstart, fend, npts) spectra = dict(zip(freq_list,
ipsec)) return spectra
*/
