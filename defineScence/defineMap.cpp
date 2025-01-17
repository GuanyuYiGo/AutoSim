#include "defineMap.h"
Map defineMap() {
  Line line1, line2;
  Point line1_start_point, line1_end_point, line2_start_point, line2_end_point;
  // line1
  line1_start_point.x = 0.0f;
  line1_start_point.y = 0.0f;
  line1_end_point.x = 100.0f;
  line1_end_point.y = 10.f;
  line1.setID(1);
  line1.setLength(100.0f);
  line1.setWidth(0.12f);
  line1.setStartPoint(line1_start_point);
  line1.setEndPoint(line1_end_point);
  line1.setCoef({0.0f, 0.0f, 0.001f, 0.f});
  // line2
  line2.setID(2);
  line2_start_point.x = 0.0;
  line2_start_point.y = 3.5f;
  line2_end_point.x = 100.0;
  line2_end_point.y = 13.5f;
  line2.setLength(100.0);
  line2.setWidth(0.12);
  line2.setStartPoint(line2_start_point);
  line2.setEndPoint(line2_end_point);
  line2.setCoef({3.5f, 0.0f, 0.001, 0.f});

  std::vector<Line> lines;
  lines.push_back(line1);
  lines.push_back(line2);
  Map map(100.0, 100.0, lines);
  return map;
}