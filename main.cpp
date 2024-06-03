#include "file_operations.h"

int main (int argc, char *argv[]) {
    std::string file_name = argv[1];
    auto[intensities, frequencies] = readBinarySpectrum(file_name);
    return 0;
}
