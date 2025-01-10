#include "defineVehicles.h"

std::vector<Vehicle> defineVehicles() {
  Vehicle vehicle1(4.0, 2.0, true);
  vehicle1.setPosition({5.0, 51.75f}, 0.0f);
  std::vector<Vehicle> vehicles;
  vehicles.push_back(vehicle1);
  return vehicles;
}