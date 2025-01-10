#ifndef VISUALIZE_H
#define VISUALIZE_H

#include "Vehicle/vehicle.h"
#include "matplotlibcpp/matplotlibcpp.h"
#include "typedefine.h"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <vector>

class Visualizer {
public:
  void visualize_common(const Map &map, const std::vector<Vehicle> &vehicles);
  void visualizePerception(const std::vector<Line> &percetion_lines,
                           const Line &ref_line,
                           const float &acceleration_request,
                           const float &steerwheel_request);
  void plotLaneLine(const Line &line, const std::string &color);
};

#endif // VISUALIZE_H