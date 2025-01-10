#include "control.h"

void Controller::controller_common(const Line &ref_line) {
  float accerlation_request = 1.f; // TODO: longitudinal control
  float lateral_error = 2 * ref_line.getCoef()[0] +
                        ref_line.getCoef()[1] * 20.f +
                        ref_line.getCoef()[2] * 20.f * 50.f +
                        ref_line.getCoef()[3] * 20.f * 20.f * 20.f;
  float heading_error = ref_line.getCoef()[1];
  float steerwheel_request = Kp * lateral_error; // TODO: lateral control
  lateral_integral_error_ += lateral_error;
  float derivative_error = lateral_error - lateral_previous_error_;
  steerwheel_request += Ki * lateral_integral_error_ + Kd * derivative_error;
  lateral_previous_error_ = lateral_error;
  setAccelerationRequest(accerlation_request);
  setSteerwheelRequest(steerwheel_request);
}