#ifndef CONTROL_H
#define CONTROL_H
#include "typedefine.h"

class Controller {
public:
  Controller() {};
  ~Controller() {};
  // void controller_PID();
  // void controller_LQR();
  // void controller_MPC();
  void controller_common(const Line &ref_line);
  void setAccelerationRequest(float accerlation_request) {
    this->accerlation_request_ = accerlation_request;
  }
  void setSteerwheelRequest(float steerwheel_request) {
    this->steerwheel_request_ = steerwheel_request;
  }
  float getAccelerationRequest() const { return accerlation_request_; }
  float getSteerwheelRequest() const { return steerwheel_request_; }

private:
  float accerlation_request_; // m/s^2
  float steerwheel_request_;  // degree
  float lateral_integral_error_ = 0.0;
  float lateral_previous_error_ = 0.0;
  float Kp = 0.25;
  float Ki = 0.03;
  float Kd = 0.02;
};

#endif // CONTROL_H