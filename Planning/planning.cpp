#include "planning.h"

void Planner::plan_common(const std::vector<Line> &perception_lines) {
  ref_line_.clear();
  if (perception_lines[0].getID() != 0 && perception_lines[1].getID() != 0) {
    Line ref_line;
    ref_line.setID(perception_lines[0].getID() + perception_lines[1].getID());
    std::vector<float> ref_line_coef;
    for (int i = 0; i < 4; i++) {
      ref_line_coef.push_back(0.5 * perception_lines[0].getCoef()[i] +
                              0.5 * perception_lines[1].getCoef()[i]);
    }
    ref_line.setCoef(ref_line_coef);
    if (perception_lines[0].getStartPoint().x <
        perception_lines[1].getStartPoint().x) {
      ref_line.setStartPoint(perception_lines[0].getStartPoint());
    } else {
      ref_line.setStartPoint(perception_lines[1].getStartPoint());
    }
    if (perception_lines[0].getEndPoint().x >
        perception_lines[1].getEndPoint().x) {
      ref_line.setEndPoint(perception_lines[0].getEndPoint());
    } else {
      ref_line.setEndPoint(perception_lines[1].getEndPoint());
    }
    setRefLine(ref_line);
  }
}