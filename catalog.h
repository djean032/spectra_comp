#ifndef CATALOG_H
#define CATALOG_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class Catalog {
  public:
    Catalog(std::string filepath);
    int convertQuantaToInt(std::string &quanta);
	struct Line {
		double freq;
		double error;
		double logIntensity;
		int degFree;
		double lowEnergy;
		int upperDeg;
		int tag;
		int quantFmt;
		int quanta1;
		int quanta2;
		int quanta3;
		int quanta4;
		int quanta5;
		int quanta6;
        int quanta1Prime;
        int quanta2Prime;
        int quanta3Prime;
        int quanta4Prime;
        int quanta5Prime;
        int quanta6Prime;
	};
    const std::vector<Line> &getLines();
  private:
    std::vector<Line> lines;

};

#endif // !CATALOG_H
