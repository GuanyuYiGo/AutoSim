#ifndef SIMULATION_H
#define SIMULATION_H
#include "Control/control.h"
#include "Perception/perception.h"
#include "Planning/planning.h"
#include "Vehicle/vehicle.h"
#include "typedefine.h"
#include <Visualize/visualize.h>

class Simulator {
public:
  Simulator(const float &step, const float &end_time) {
    this->step = step;
    this->end_time = end_time;
  };
  ~Simulator() {};
  void RunSimulation(const Map &map, std::vector<Vehicle> &vehicles);
  void StepSimulation(const Map &map, std::vector<Vehicle> &vehicles);
  void endSimulation();

private:
  Visualizer visualizer;
  float end_time;
  float step;
};
#endif // SIMULATION_H