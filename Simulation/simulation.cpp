#include "simulation.h"

void Simulator::StepSimulation(const Map &map, std::vector<Vehicle> &vehicles) {
  for (auto &vehicle : vehicles) {
    if (vehicle.getisEgo()) {
      std::vector<Line> sensor_detect_lines;
      vehicle.lane_mark_sensor.UpdateAndGetLineMarkCoef(
          map, vehicle.getPosition(), vehicle.getTheta(), sensor_detect_lines);
      vehicle.perceptioner.percepation_common(map, sensor_detect_lines);
      vehicle.planner.plan_common(vehicle.perceptioner.getPerceptionLines());
      vehicle.controller.controller_common(
          vehicle.planner.getRefLine(), vehicle.getVelocity(),
          vehicle.getSteeringAngle(), vehicle.getTheta(), vehicle.getLength());
      visualizer.visualizePerception(
          vehicle.perceptioner.getPerceptionLines(),
          vehicle.planner.getRefLine(),
          vehicle.controller.getAccelerationRequest(),
          vehicle.controller.getSteerwheelRequest());
      vehicle.updateBicycleModel(vehicle.controller.getAccelerationRequest(),
                                 vehicle.controller.getSteerwheelRequest());
    } else {
      // TODO: Implement the behavior of non-ego vehicles
      continue;
    }
  }
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
