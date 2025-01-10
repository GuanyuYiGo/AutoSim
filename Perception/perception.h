#ifndef PERCEPATION_H
#define PERCEPATION_H

#include "LaneMarkSensor/LaneMarkSensor.h"
#include "typedefine.h"
#include <vector>

class Perception {
public:
  Perception() {};
  ~Perception() {};
  void percepation_common(const Map &map,
                          const std::vector<Line> &sensor_detected_lines);
  void setPerceptionLines(std::vector<Line> perception_lines) {
    this->perception_lines = perception_lines;
  }
  std::vector<Line> getPerceptionLines() { return perception_lines; }
  void reasonLaneMarks(const std::vector<Line> &sensor_detect_lines);

private:
  std::vector<Line> perception_lines;
};

#endif // PERCEPATION_H