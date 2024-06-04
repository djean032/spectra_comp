#include "catalog.h"

Catalog::Catalog(std::string filepath) {
	std::vector<Line> catalogLines;
	std::ifstream inputFile(filepath);
	std::string line;
	while (std::getline(inputFile, line)) {
		Line l;
		std::string quanta1, quanta2, quanta3, quanta4, quanta5, quanta6;
		std::string quanta1Prime, quanta2Prime, quanta3Prime, quanta4Prime,
			quanta5Prime, quanta6Prime;
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

std::vector<Catalog::Line> Catalog::selectSeries() {
    std::vector<Catalog::Line> series(this->getLines());
    int quanta, selectionRule;
    std::cout << "Enter quanta and selection rule separated by space:\n" << "ex. for a-type R-branch 0,1 transitions, you would enterl '2 0' for deltaKa = 0, followed by '1 0' for R-branch, and finally '1 1' for deltaKc = 1\n";
    while (std::cin >> quanta >> selectionRule) {
        series.erase(std::remove_if(series.begin(), series.end(), [quanta, selectionRule](const Catalog::Line &line) {
            switch (quanta) {
                case 1:
                    return line.quanta1Prime - line.quanta1 != selectionRule;
                case 2:
                    return line.quanta2Prime - line.quanta2 != selectionRule;
                case 3:
                    return line.quanta3Prime - line.quanta3 != selectionRule;
                case 4:
                    return line.quanta4Prime - line.quanta4 != selectionRule;
                case 5:
                    return line.quanta5Prime - line.quanta5 != selectionRule;
                case 6:
                    return line.quanta6Prime - line.quanta6 != selectionRule;
                default:
                    return true;
            }
        }), series.end());
        std::cout << "Enter quanta and selection rule separated by space: ";
    }
    return series;
}
