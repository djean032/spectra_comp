#include "file_operations.h"
#include <chrono>

int main (int argc, char *argv[]) {
    std::string file_name = argv[1];
    auto begin = std::chrono::high_resolution_clock::now();
    Spectrum cyanomethcycloprop = Spectrum(file_name);
    Catalog cyanomethcycloprop_catalog = Catalog(argv[2]);
    std::vector<Catalog::Line> catLines = cyanomethcycloprop_catalog.getLines();
    std::cout << "Number of lines in catalog: " << catLines.size() << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to read binary spectrum: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    return 0;
}
