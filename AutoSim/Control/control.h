#ifndef CONTROL_H
#define CONTROL_H
#include "typedefine.h"
#include <Vehicle/vehicle.h>

class Controller {
public:
  Controller() {};
  ~Controller() {};
  void controller_common(std::vector<Vehicle> &vehicles);
};

#endif // CONTROL_H