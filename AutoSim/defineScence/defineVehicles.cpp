#include "defineVehicles.h"

std::vector<Vehicle> defineVehicles() {
  Vehicle vehicle1(4.0, 2.0);
  vehicle1.setPosition({5.0, 50.75f}, 0.0f);
  std::vector<Vehicle> vehicles;
  vehicles.push_back(vehicle1);
  return vehicles;
}