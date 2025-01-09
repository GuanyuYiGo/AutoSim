#include "vehicle.h"

void Vehicle::updateBicycleModel(float acceleration, float steering_angle) {
  float delta_t = 0.02f;
  float front_wheel_angle = steering_angle * 0.04 * deg2rad;
  float theta_dot = velocity_ * tan(front_wheel_angle) / length_;
  float x_dot = velocity_ * std::cos(theta_);
  float y_dot = velocity_ * std::sin(theta_);
  position_.x += x_dot * delta_t;
  position_.y += y_dot * delta_t;
  theta_ += theta_dot * delta_t;
  velocity_ += acceleration * delta_t;
  steering_angle_ = steering_angle;
}