#include "catalog.h"
#include "spectrum.h"
#include <chrono>

int main(int argc, char *argv[]) {
	std::string spectrumFilename = argv[1];
	std::string catalogFilename = argv[2];
	auto begin = std::chrono::high_resolution_clock::now();
	Spectrum cyanomethcycloprop = Spectrum(spectrumFilename);
	Catalog cyanomethcycloprop_catalog = Catalog(argv[2]);
    auto series = cyanomethcycloprop_catalog.selectSeries();
    for (int i = 0; i < 10; ++i) {
        std::cout << series[i].freq << " " << series[i].quanta1 << " " << series[i].quanta2 << " " << series[i].quanta3 << " " << series[i].quanta4 << " " << series[i].quanta5 << " " << series[i].quanta6 << " " << series[i].quanta1Prime << " " << series[i].quanta2Prime << " " << series[i].quanta3Prime << " " << series[i].quanta4Prime << " " << series[i].quanta5Prime << " " << series[i].quanta6Prime << std::endl;
    }
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Time elapsed: "
			  << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
																	  begin)
						 .count() /
					 1e9
			  << " s\n";
	return 0;
}
