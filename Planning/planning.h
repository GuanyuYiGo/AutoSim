#ifndef PLANNING_H
#define PLANNING_H

#include "typedefine.h"

class Planner {
public:
  Planner() {};
  ~Planner() {};
  void plan_common(const std::vector<Line> &perception_lines);
  void setRefLine(const Line &ref_line) { this->ref_line_ = ref_line; }
  Line getRefLine() const { return ref_line_; }

  //   void LatticePlanner();
  //   void EMPlanner();
  //   void PromdpPlanner();
private:
  Line ref_line_;
};
#endif // PLANNING_H
