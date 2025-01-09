#ifndef CURVE_H
#define CURVE_H

#ifndef PCH_H
#include "typedefine.h"
#include <cmath>
#include <vector>
#endif // PCH_H
#include <algorithm>
#include <array>

#include <complex>
#include <numeric>

bool solveCubic(float a, float b, float c, float d, std::vector<float> &roots);
bool fitCubicPoly(const std::vector<Point> &points, std::vector<float> &coef,
                  const Point &origin);

#endif // CURVE_H