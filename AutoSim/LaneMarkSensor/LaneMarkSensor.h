#ifndef LANEMARKSENSOR_H
#define LANEMARKSENSOR_H

#ifndef PCH_H
#include "typedefine.h"
#include <cmath>
#include <vector>
#endif // PCH_H

#include <Math/curve.h>
#include <unordered_map>

class LaneMarkSensor {
public:
  LaneMarkSensor() {};
  LaneMarkSensor(Point install_location, float lateral_check_range,
                 float longitudinal_check_range) {
    this->install_location = install_location;
    this->lateral_check_range = lateral_check_range;
    this->longitudinal_check_range = longitudinal_check_range;
  }

  void SetInstallLocation(Point install_location) {
    this->install_location = install_location;
  }
  void SetLateralCheckRange(float lateral_check_range) {
    this->lateral_check_range = lateral_check_range;
  }
  void SetLongitudinalCheckRange(float longitudinal_check_range) {
    this->longitudinal_check_range = longitudinal_check_range;
  }
  Point getInstallLocation() { return install_location; }
  float getLateralCheckRange() { return lateral_check_range; }
  float getLongitudinalCheckRange() { return longitudinal_check_range; }
  bool UpdateAndGetLineMarkCoef(const Map &map, const Point &vehicle_pos,
                                const float &vehicle_heading,
                                std::vector<Line> &perception_lines);
  void setCheckRangeCorners(std::vector<Point> check_range_corners) {
    this->check_range_corners = check_range_corners;
  }
  std::vector<Point> getCheckRangeCorners() { return check_range_corners; }
  // std::vector<Line> getInRangeLines(const Map &map,
  //                                   const std::vector<Point> &corners,
  //                                   std::vector<Line> &in_range_lines);
  void generateLMSDetectLine(const float &step_distance,
                             const float &step_number, const Point &startpoint1,
                             const Point &startpoint2);
  std::vector<Line> getLMSDetectLines() { return LMSDetectLines; }
  bool detectIntersection(const Line &map_line, const Line &detect_line,
                          Point &intersection_point);
  void convertToVehicleCoordinate(std::vector<Point> &point_set,
                                  const Point &vehicle_pos,
                                  const float &vehicle_heading);

private:
  Point install_location{0.0f, 0.0f};     // relative to the ground
  float install_heading = 0.f;            // rad, relative to the ground
  std::vector<Point> check_range_corners; // relative to the ground
  float lateral_check_range = 15.f;
  float longitudinal_check_range = 80.f;
  std::vector<Line> LMSDetectLines;
};

#endif // LANEMARKSENSOR_H