#include "perception.h"

void Perception::reasonLaneMarks(std::vector<Line> &perception_lines) {
  Line left_lane_line, right_lane_line, left_left_lane_line,
      right_right_lane_line;

  for (const Line &perception_line : perception_lines) {
    float c0 = perception_line.getCoef()[0];
    if (std::abs(c0) > 7.5f) {
      continue;
    }

    // 分类左车道线和左左车道线
    if (c0 > 0.f && c0 <= 3.5f) {
      if (left_lane_line.getID() == 0) {
        left_lane_line = perception_line;
      } else {
        if (c0 < left_lane_line.getCoef()[0]) {
          if (left_left_lane_line.getID() == 0) {
            left_left_lane_line = left_lane_line;
            left_lane_line = perception_line;
          } else {
            if (left_lane_line.getCoef()[0] <
                left_left_lane_line.getCoef()[0]) {
              left_left_lane_line = left_lane_line;
              left_lane_line = perception_line;
            }
          }
        } else if (left_left_lane_line.getID() == 0 ||
                   c0 < left_left_lane_line.getCoef()[0]) {
          left_left_lane_line = perception_line;
        }
      }
    }

    // 分类右车道线和右右车道线
    if (c0 <= 0.f && c0 >= -3.5f) {
      if (right_lane_line.getID() == 0) {
        right_lane_line = perception_line;
      } else {
        if (c0 > right_lane_line.getCoef()[0]) {
          if (right_right_lane_line.getID() == 0) {
            right_right_lane_line = right_lane_line;
            right_lane_line = perception_line;
          } else {
            if (right_lane_line.getCoef()[0] >
                right_right_lane_line.getCoef()[0]) {
              right_right_lane_line = right_lane_line;
              right_lane_line = perception_line;
            }
          }
        } else if (right_right_lane_line.getID() == 0 ||
                   c0 > right_right_lane_line.getCoef()[0]) {
          right_right_lane_line = perception_line;
        }
      }
    }
  }

  // 清空原始 perception_lines 并重新排序
  perception_lines.clear();
  perception_lines.push_back(left_lane_line);
  perception_lines.push_back(right_lane_line);
  perception_lines.push_back(left_left_lane_line);
  perception_lines.push_back(right_right_lane_line);
}

void Perception::percepation_common(const Map &map,
                                    std::vector<Vehicle> &vehicles) {
  std::vector<Line> perception_lines_temp;
  for (Vehicle &vehicle : vehicles) {
    vehicle.lane_mark_sensor.UpdateAndGetLineMarkCoef(
        map, vehicle.getPosition(), vehicle.getTheta(), perception_lines_temp);
    int a = 0;
  }
  reasonLaneMarks(perception_lines_temp);
  setPerceptionLines(perception_lines_temp);
}
