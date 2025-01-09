#include "control.h"

void Controller::controller_common(std::vector<Vehicle> &vehicles) {
  for (Vehicle &vehicle : vehicles) {
    vehicle.updateBicycleModel(1.f, 5.f);
  }
}