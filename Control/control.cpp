#include "control.h"

void Controller::controller_common(const Line &ref_line, const float &velocity,
                                   const float &steerwheel_angle,
                                   const float &heading,
                                   const float &wheel_base) {
  // This controller is a simple controller that sets the acceleration request
  // to 0 and the steering wheel request based ref line and bicycle model.
  float acceleration_request = 0.f; // TODO: longitudinal control
  float steerwheel_request = 0.f;
  if (ref_line.getID() != 0) {
    float desired_y = ref_line.getCoef()[0];
    float desired_theta = std::asin(desired_y / velocity);
    float desired_frontwheel_rad =
        std::atan((desired_theta - heading) * wheel_base / velocity);
    steerwheel_request = desired_frontwheel_rad * rad2deg * 25.f;
  }
  setAccelerationRequest(acceleration_request);
  setSteerwheelRequest(steerwheel_request);
}