#ifndef VEHICLE_H
#define VEHICLE_H

#include "Control/control.h"
#include "LaneMarkSensor/LaneMarkSensor.h"
#include "Perception/perception.h"
#include "Planning/planning.h"
#include "typedefine.h"

class Vehicle {
public:
  Vehicle(float length, float width, bool is_ego) {
    this->length_ = length;
    this->width_ = width;
    this->is_ego_ = is_ego;
  }
  bool getisEgo() const { return is_ego_; }
  void setisEgo(bool is_ego) { this->is_ego_ = is_ego; }
  float getLength() { return length_; }
  float getWidth() const { return width_; }
  void setTheta(float theta) { this->theta_ = theta; }
  float getTheta() const { return theta_; }
  void setPosition(Point position, float heading) {
    this->position_ = position;
    this->theta_ = heading;
  }
  Point getPosition() const { return position_; }
  LaneMarkSensor lane_mark_sensor{position_, 15.f, 80.f};
  Perception perceptioner;
  Planner planner;
  Controller controller;
  void updateBicycleModel(float acceleration, float steering_angle);

private:
  bool is_ego_;
  float velocity_ = 10.f;       // m/s
  float acceleration_ = 0.0f;   // m/s^2
  float steering_angle_ = 0.0f; // deg
  float length_;                // m
  float width_;                 // m
  float theta_;                 // rad, relative to the ground
  Point position_;              // relative to the ground
};
#endif // VEHICLE_H