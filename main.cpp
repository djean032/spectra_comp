#include "catalog.h"
#include "spectrum.h"
#include "stacking.h"

int main(int argc, char *argv[]) {
	std::string spectrumFilename = argv[1];
	std::string catalogFilename = argv[2];
	Spectrum cyanomethcycloprop = Spectrum(spectrumFilename);
	Catalog cyanomethcycloprop_catalog = Catalog(argv[2]);
	auto series = cyanomethcycloprop_catalog.selectSeries();
	std::cout << "Series size: " << series.size() << std::endl;
	/*
	for (auto &line : series) {
		std::cout << line.freq << " " << line.quanta1 << " " << line.quanta2
				  << " " << line.quanta3 << " " << line.quanta4 << " "
				  << line.quanta5 << " " << line.quanta6 << " "
				  << line.quanta1Prime << " " << line.quanta2Prime << " "
				  << line.quanta3Prime << " " << line.quanta4Prime << " "
				  << line.quanta5Prime << " " << line.quanta6Prime << std::endl;
	}
	*/
	auto stackedIntensities = stacked(series, cyanomethcycloprop, 500);
    std::ofstream output("output.txt");
    for (auto &intensity : stackedIntensities) {
        output << intensity << std::endl;
    }
	return 0;
}
