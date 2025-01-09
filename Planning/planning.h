#ifndef PLANNING_H
#define PLANNING_H

#include "typedefine.h"
#include <Vehicle/vehicle.h>

class Planner {
public:
  Planner() {};
  ~Planner() {};
  void plan_common(std::vector<Vehicle> &vehicles);
  //   void LatticePlanner();
  //   void EMPlanner();
  //   void PromdpPlanner();
};
#endif // PLANNING_H
