#include "simulation.h"

void Simulator::StepSimulation(const Map &map, std::vector<Vehicle> &vehicles) {
  perceptioner.percepation_common(map, vehicles);
  visualizer.visualizePerception(perceptioner.getPerceptionLines());
  planner.plan_common(vehicles);
  controller.controller_common(vehicles);
  visualizer.visualize_common(map, vehicles);
}

void Simulator::endSimulation() { return; }

void Simulator::RunSimulation(const Map &map, std::vector<Vehicle> &vehicles) {
  double current_time = 0.0;
  while (current_time < end_time) {
    StepSimulation(map, vehicles);
    current_time += step;
  }
  endSimulation();
  return;
}
