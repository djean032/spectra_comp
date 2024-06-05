#ifndef STACKING_H
#define STACKING_H

#include "catalog.h"
#include "spectrum.h"
#include <cfloat>

std::vector<double> stacked(const std::vector<Catalog::Line> &lines, const Spectrum &spectrum);

#endif // !STACKING_H
