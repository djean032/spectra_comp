#include "stacking.h"

std::vector<double> stacked(const std::vector<Catalog::Line> &lines,
						 const Spectrum &spectrum, const int &window) {
	// get freqs of picked lines
	std::vector<double> pickFreqs;
	std::vector<int> stackIndices;
	std::vector<std::vector<int>> pickedIntensities;
    int windowHalfSize = window;
    std::vector<double> freqs = spectrum.getFreqs();
    std::vector<int> intensities = spectrum.getIntensities();
    double min_freq = std::min_element(freqs.begin(), freqs.end())[0];
    double max_freq = std::max_element(freqs.begin(), freqs.end())[0];
	for (auto &line : lines) {
        if (line.freq >= min_freq && line.freq <= max_freq) {
            pickFreqs.push_back(line.freq);
        } else {
            continue;
        }
	}



	for (auto &freq : pickFreqs) {
        int index = std::lower_bound(freqs.begin(), freqs.end(), freq) - freqs.begin();
        stackIndices.push_back(index);
	}

	for (auto &index : stackIndices) {
		if (index < windowHalfSize) {
			std::vector<int> tmp(windowHalfSize - index, 0);
			std::copy(intensities.begin(), intensities.begin() + index + windowHalfSize,
					  std::back_inserter(tmp));
			pickedIntensities.push_back(tmp);
		} else if (index > intensities.size() - windowHalfSize) {
			std::vector<int> tmp;
			std::copy(intensities.begin() + index - windowHalfSize, intensities.end(),
					  std::back_inserter(tmp));
			tmp.resize(2 * windowHalfSize, 0);
			pickedIntensities.push_back(tmp);
		} else {
			std::vector<int> tmp;
			std::copy(intensities.begin() + index - windowHalfSize,
					  intensities.begin() + index + windowHalfSize, std::back_inserter(tmp));
			pickedIntensities.push_back(tmp);
		}
	}
    

    std::vector<double> sumIntensities(2 * windowHalfSize, 0.0);
    std::vector<std::vector<double>> pickedIntensitiesDouble;
    std::transform(pickedIntensities.begin(), pickedIntensities.end(), std::back_inserter(pickedIntensitiesDouble), [](std::vector<int> &intensity) {
        std::vector<double> tmp;
        std::transform(intensity.begin(), intensity.end(), std::back_inserter(tmp), [](int &intensity) {
            return static_cast<double>(intensity);
        });
        return tmp;
    });
    for (auto &intensity : pickedIntensitiesDouble) {
        std::transform(sumIntensities.begin(), sumIntensities.end(), intensity.begin(), sumIntensities.begin(), std::plus<double>());
    }
    return sumIntensities;
}
