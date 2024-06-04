#include "catalog.h"
#include "spectrum.h"
#include <chrono>

int main(int argc, char *argv[]) {
	std::string spectrumFilename = argv[1];
	std::string catalogFilename = argv[2];
	auto begin = std::chrono::high_resolution_clock::now();
	Spectrum cyanomethcycloprop = Spectrum(spectrumFilename);
	Catalog cyanomethcycloprop_catalog = Catalog(argv[2]);
	std::vector<Catalog::Line> catLines = cyanomethcycloprop_catalog.getLines();
	for (auto &line : catLines) {
		if (line.quanta2 == line.quanta2Prime) {
			std::cout << line.freq << " " << line.error << " "
					  << line.logIntensity << " " << line.degFree << " "
					  << line.lowEnergy << " " << line.upperDeg << " "
					  << line.tag << " " << line.quantFmt << " " << line.quanta1
					  << " " << line.quanta2 << " " << line.quanta3 << " "
					  << line.quanta4 << " " << line.quanta5 << " "
					  << line.quanta6 << " " << line.quanta1Prime << " "
					  << line.quanta2Prime << " " << line.quanta3Prime << " "
					  << line.quanta4Prime << " " << line.quanta5Prime << " "
					  << line.quanta6Prime << std::endl;
		} else {
			continue;
		}
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
