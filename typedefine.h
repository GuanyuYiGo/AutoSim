#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

#include <vector>

struct Point {
  float x;
  float y;
};

const float deg2rad = 0.017453;
class Line {
public:
  Line() {}
  Line(int ID, float length, float width, Point start_point, Point end_point,
       std::vector<float> coef) {
    this->ID = ID;
    this->length = length;
    this->width = width;
    this->start_point = start_point;
    this->end_point = end_point;
    this->coef = coef;
    this->is_vertical = false;
  }
  void setID(int ID) { this->ID = ID; }
  void setLength(float length) { this->length = length; }
  void setWidth(float width) { this->width = width; }
  void setStartPoint(Point start_point) { this->start_point = start_point; }
  void setEndPoint(Point end_point) { this->end_point = end_point; }
  void setCoef(std::vector<float> coef) { this->coef = coef; }
  void setIsVertical(bool is_vertical) { this->is_vertical = is_vertical; }
  int getID() const { return ID; }
  float getLength() { return length; }
  float getWidth() { return width; }
  Point getStartPoint() const { return start_point; }
  Point getEndPoint() const { return end_point; }
  std::vector<float> getCoef() const { return coef; }
  bool getIsVertical() const { return is_vertical; }

private:
  bool is_vertical = false;
  int ID = 0;
  float length;
  float width;
  Point start_point;
  Point end_point;
  std::vector<float> coef;
};

class Map {
public:
  Map() {}
  Map(float length, float width, std::vector<Line> lines) {
    this->length = length;
    this->width = width;
    this->lines = lines;
  }

  float length;
  float width;
  std::vector<Line> lines;
};

#endif // TYPEDEFINE_H