#include "pch.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  double simulation_time = 5.0;
  double step = 0.02;
  double current_time = 0.0;
  Map map = defineMap();
  std::vector<Vehicle> vehicles = defineVehicles();

  Simulator simulator(step, simulation_time);
  simulator.RunSimulation(map, vehicles);

  return 0;
}