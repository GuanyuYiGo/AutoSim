#include "LaneMarkSensor.h"

void LaneMarkSensor::generateLMSDetectLine(const float &step_distance,
                                           const float &step_number,
                                           const Point &startpoint1,
                                           const Point &startpoint2) {
  Point mid_point;
  mid_point.x = 0.5f * (startpoint1.x + startpoint2.x);
  mid_point.y = 0.5f * (startpoint1.y + startpoint2.y);

  // mid point vertical line
  float dx = startpoint1.x - startpoint2.x;
  float dy = startpoint1.y - startpoint2.y;
  float length = std::sqrt(dx * dx + dy * dy);
  float ux_act = dx / length;
  float uy_act = dy / length;
  float ux = std::abs(ux_act) > 0.1f ? ux_act : 0.f;
  float uy = std::abs(uy_act) > 0.1f ? uy_act : 0.f;
  LMSDetectLines.clear();
  LMSDetectLines.reserve(39);
  for (int i = 0; i < step_number; ++i) {
    float offset = step_distance * (i + 1);
    Point new_start_point1, new_start_point2;
    new_start_point1.x = startpoint1.x + offset * uy;
    new_start_point1.y = startpoint1.y + offset * ux;
    new_start_point2.x = startpoint2.x + offset * uy;
    new_start_point2.y = startpoint2.y + offset * ux;
    Line line;
    line.setStartPoint(new_start_point1);
    line.setEndPoint(new_start_point2);
    line.setLength(length);
    float line_c0, line_c1;
    if (std::abs(ux) < 1e-6) {
      line.setIsVertical(true);
      line_c0 = new_start_point1.x;
      line_c1 = 0.f;
    } else if (std::abs(uy) < 1e-6) {
      line_c0 = new_start_point1.y;
      line_c1 = 0.f;
    } else {
      line_c1 = (new_start_point1.y - new_start_point2.y) /
                (new_start_point1.x - new_start_point2.x);
      line_c0 = new_start_point1.y - line_c1 * new_start_point1.x;
    }
    line.setCoef({line_c0, line_c1, 0.f, 0.f});
    LMSDetectLines.push_back(std::move(line));
  }
  int a = 1;
}

bool LaneMarkSensor::detectIntersection(const Line &map_line,
                                        const Line &detect_line,
                                        Point &intersection_point) {
  const std::vector<float> &map_coef = map_line.getCoef();
  const std::vector<float> &detect_coef = detect_line.getCoef();
  if (detect_line.getIsVertical()) {
    float x = detect_coef[0];
    float valid_y_low =
        std::min(map_line.getStartPoint().y, map_line.getEndPoint().y);
    float valid_y_up =
        std::max(map_line.getStartPoint().y, map_line.getEndPoint().y);
    float y_map = map_coef[3] * x * x * x + map_coef[2] * x * x +
                  map_coef[1] * x + map_coef[0];
    if (y_map >= valid_y_low && y_map <= valid_y_up) {
      intersection_point.x = x;
      intersection_point.y = y_map;
      return true;
    }
    return false;
  }

  // 求解一元三次方程
  float a = map_coef[3];
  float b = map_coef[2];
  float c = map_coef[1] - detect_coef[1];
  float d = map_coef[0] - detect_coef[0];
  std::vector<float> roots;
  float valid_x_low = std::min(
      std::min(map_line.getStartPoint().x, map_line.getEndPoint().x),
      std::min(detect_line.getStartPoint().x, detect_line.getEndPoint().x));
  float valid_x_up = std::max(
      std::max(map_line.getStartPoint().x, map_line.getEndPoint().x),
      std::max(detect_line.getStartPoint().x, detect_line.getEndPoint().x));
  float valid_y_low = std::min(
      std::min(map_line.getStartPoint().y, map_line.getEndPoint().y),
      std::min(detect_line.getStartPoint().y, detect_line.getEndPoint().y));
  float valid_y_up = std::max(
      std::max(map_line.getStartPoint().y, map_line.getEndPoint().y),
      std::max(detect_line.getStartPoint().y, detect_line.getEndPoint().y));
  if (solveCubic(a, b, c, d, roots)) {
    for (float root : roots) {
      if (root >= valid_x_low && root <= valid_x_up) {
        // 计算交点的 y 坐标
        float y_map = map_coef[3] * root * root * root +
                      map_coef[2] * root * root + map_coef[1] * root +
                      map_coef[0];
        float y_detect = detect_coef[1] * root + detect_coef[0];
        if (y_map >= valid_y_low && y_map <= valid_y_up &&
            y_detect >= valid_y_low && y_detect <= valid_y_up) {
          intersection_point.x = root;
          intersection_point.y = y_map;
          return true;
        }
      }
    }
  }

  return false;
}

void LaneMarkSensor::convertToVehicleCoordinate(std::vector<Point> &point_set,
                                                const Point &vehicle_pos,
                                                const float &vehicle_heading) {
  float cos_theta = std::cos(vehicle_heading);
  float sin_theta = std::sin(vehicle_heading);
  for (Point &point : point_set) {
    float x = point.x - vehicle_pos.x;
    float y = point.y - vehicle_pos.y;
    point.x = x * cos_theta + y * sin_theta;
    point.y = -x * sin_theta + y * cos_theta;
  }
}

bool LaneMarkSensor::UpdateAndGetLineMarkCoef(
    const Map &map, const Point &vehicle_pos, const float &vehicle_heading,
    std::vector<Line> &perception_lines) {
  install_location.x = vehicle_pos.x;
  install_location.y = vehicle_pos.y;
  install_heading = vehicle_heading;
  // check range
  /*
  检测区域示意图：车辆车头朝向为纵向检测方向，与之垂直的方向为横向检测方向

       corner1  +------------------+  corner2
                |                  |
install location.                  |
                |                  |
       corner4  +------------------+  corner3
*/
  Point corner1, corner2, corner3, corner4;
  corner1.x = install_location.x -
              lateral_check_range * std::sin(install_heading) * 0.5f;
  corner1.y = install_location.y +
              lateral_check_range * std::cos(install_heading) * 0.5f;
  corner2.x = install_location.x +
              longitudinal_check_range * std::cos(install_heading) -
              lateral_check_range * std::sin(install_heading) * 0.5f;
  corner2.y = install_location.y +
              longitudinal_check_range * std::sin(install_heading) +
              lateral_check_range * std::cos(install_heading) * 0.5f;
  corner3.x = install_location.x +
              longitudinal_check_range * std::cos(install_heading) +
              lateral_check_range * std::sin(install_heading) * 0.5f;
  corner3.y = install_location.y +
              longitudinal_check_range * std::sin(install_heading) -
              lateral_check_range * std::cos(install_heading) * 0.5f;
  corner4.x = install_location.x +
              lateral_check_range * std::sin(install_heading) * 0.5f;
  corner4.y = install_location.y -
              lateral_check_range * std::cos(install_heading) * 0.5f;
  setCheckRangeCorners({corner1, corner2, corner3, corner4});
  // step is 2m, corner1->corner4 is first detected line until corner2->
  // corner3
  float lms_step = 2.f;
  generateLMSDetectLine(lms_step, 39.f, corner1, corner4);
  // traverse all lines in map to find the lines which have intersection
  // points
  std::unordered_map<int, std::vector<Point>> intersection_points;
  for (const Line &map_line : map.lines) {
    for (const Line &detect_line : LMSDetectLines) {
      Point intersection;
      if (detectIntersection(map_line, detect_line, intersection)) {
        intersection_points[map_line.getID()].push_back(intersection);
      }
    }
  }
  if (intersection_points.empty()) {
    return false;
  }
  for (auto &intersection_point : intersection_points) {
    convertToVehicleCoordinate(intersection_point.second, vehicle_pos,
                               vehicle_heading);
  }
  bool detect_any_line = false;
  int index = 0;
  for (const auto &pair : intersection_points) {
    if (pair.first != 0) {
      std::vector<Point> point_to_fit;
      point_to_fit.insert(point_to_fit.end(), pair.second.begin(),
                          pair.second.end());
      std::vector<float> coef_temp;
      if (fitCubicPoly(point_to_fit, coef_temp, install_location)) {
        if (index >= perception_lines.size()) {
          perception_lines.push_back(Line());
        }
        perception_lines[index].setCoef(coef_temp);
        perception_lines[index].setStartPoint(point_to_fit.front());
        perception_lines[index].setEndPoint(point_to_fit.back());
        perception_lines[index].setLength(std::sqrt(
            std::pow(point_to_fit.front().x - point_to_fit.back().x, 2) +
            std::pow(point_to_fit.front().y - point_to_fit.back().y, 2)));
        perception_lines[index].setID(pair.first);
        detect_any_line = true;
        ++index;
      }
    }
  }
  return detect_any_line;
}