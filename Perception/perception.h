#ifndef PERCEPATION_H
#define PERCEPATION_H

#include "LaneMarkSensor/LaneMarkSensor.h"
#include "Vehicle/vehicle.h"
#include "typedefine.h"
#include <vector>

class Perception {
public:
  Perception() {};
  ~Perception() {};
  void percepation_common(const Map &map, std::vector<Vehicle> &vehicles);
  void setPerceptionLines(std::vector<Line> perception_lines) {
    this->perception_lines = perception_lines;
  }
  std::vector<Line> getPerceptionLines() { return perception_lines; }
  void reasonLaneMarks(std::vector<Line> &perception_lines);

private:
  std::vector<Line> perception_lines;
};

#endif // PERCEPATION_H