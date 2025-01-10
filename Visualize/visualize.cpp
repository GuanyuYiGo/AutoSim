#include "visualize.h"

namespace py = pybind11;
namespace plt = matplotlibcpp;

void Visualizer::visualize_common(const Map &map,
                                  const std::vector<Vehicle> &vehicles) {
  plt::figure(1);
  plt::clf();
  plt::xlim(0.0f, std::max(map.length, map.width));
  plt::ylim(0.0f, std::max(map.length, map.width));
  // plt::xlim(0.0f, 20.0f);
  // plt::ylim(0.0f, 20.0f);

  // 绘制车道线
  for (const Line &line : map.lines) {
    std::vector<float> x, y;
    for (float i = line.getStartPoint().x; i <= line.getEndPoint().x;
         i += 0.1f) {
      x.push_back(i);
      y.push_back(line.getCoef()[0] + line.getCoef()[1] * i +
                  line.getCoef()[2] * i * i + line.getCoef()[3] * i * i * i);
    }
    plt::plot(x, y, "k-");
  }

  // 绘制车辆
  for (Vehicle vehicle : vehicles) {
    Point position = vehicle.getPosition();
    float length = vehicle.getLength();
    float width = vehicle.getWidth();
    float x = position.x;
    float y = position.y;
    float theta_rad = vehicle.getTheta();

    std::vector<float> x_coords, y_coords;
    std::vector<float> lms_x_coords, lms_y_coords;
    x_coords.push_back(x + length / 2 * cos(theta_rad) -
                       width / 2 * sin(theta_rad));
    y_coords.push_back(y + length / 2 * sin(theta_rad) +
                       width / 2 * cos(theta_rad));
    x_coords.push_back(x + length / 2 * cos(theta_rad) +
                       width / 2 * sin(theta_rad));
    y_coords.push_back(y + length / 2 * sin(theta_rad) -
                       width / 2 * cos(theta_rad));
    x_coords.push_back(x - length / 2 * cos(theta_rad) +
                       width / 2 * sin(theta_rad));
    y_coords.push_back(y - length / 2 * sin(theta_rad) -
                       width / 2 * cos(theta_rad));
    x_coords.push_back(x - length / 2 * cos(theta_rad) -
                       width / 2 * sin(theta_rad));
    y_coords.push_back(y - length / 2 * sin(theta_rad) +
                       width / 2 * cos(theta_rad));

    // 连接回第一个点，形成闭合的矩形
    x_coords.push_back(x_coords[0]);
    y_coords.push_back(y_coords[0]);

    // 绘制lane mark sensor检测范围
    std::vector<Point> check_range_corners =
        vehicle.lane_mark_sensor.getCheckRangeCorners();
    for (int i = 0; i < 4; i++) {
      lms_x_coords.push_back(check_range_corners[i].x);
      lms_y_coords.push_back(check_range_corners[i].y);
    }
    lms_x_coords.push_back(check_range_corners[0].x);
    lms_y_coords.push_back(check_range_corners[0].y);

    // 绘制lane mark sensor检测线
    std::vector<Line> LMSDetectLines =
        vehicle.lane_mark_sensor.getLMSDetectLines();
    if (!LMSDetectLines.empty()) {
      // 绘制第一条线
      Line first_line = LMSDetectLines.front();
      std::vector<float> x_first, y_first;
      x_first.push_back(first_line.getStartPoint().x);
      y_first.push_back(first_line.getStartPoint().y);
      x_first.push_back(first_line.getEndPoint().x);
      y_first.push_back(first_line.getEndPoint().y);
      plt::plot(x_first, y_first, "y--");

      // 绘制最后一条线
      Line last_line = LMSDetectLines.back();
      std::vector<float> x_last, y_last;
      x_last.push_back(last_line.getStartPoint().x);
      y_last.push_back(last_line.getStartPoint().y);
      x_last.push_back(last_line.getEndPoint().x);
      y_last.push_back(last_line.getEndPoint().y);
      plt::plot(x_last, y_last, "y--");
    }

    plt::plot(x_coords, y_coords, "b-");
    plt::plot(lms_x_coords, lms_y_coords, "g--");
  }

  plt::pause(0.01);
}

void Visualizer::plotLaneLine(const Line &line, const std::string &color) {
  std::vector<float> x, y;
  for (float i = line.getStartPoint().x; i <= line.getEndPoint().x; i += 0.1f) {
    x.push_back(i);
    y.push_back(line.getCoef()[0] + line.getCoef()[1] * i +
                line.getCoef()[2] * i * i + line.getCoef()[3] * i * i * i);
  }
  plt::plot(x, y, color);
}

void Visualizer::visualizePerception(const std::vector<Line> &percetion_lines,
                                     const Line &ref_line,
                                     const float &acceleration_request,
                                     const float &steerwheel_request) {
  plt::figure(2);
  py::object plt = py::module::import("matplotlib.pyplot");
  plt.attr("figure")(2);
  // 获取当前图窗并设置位置和大小
  py::object manager = plt.attr("gcf")().attr("canvas").attr("manager");
  py::object window = manager.attr("window");
  window.attr("wm_geometry")("800x800+1120+0"); // 设置窗口大小为 800x600

  plt::clf();
  plt::xlim(0.0f, 100.0f);
  plt::ylim(-10.0f, 10.0f);
  plt::set_aspect(1);

  // 绘制左车道线
  if (percetion_lines[0].getID() != 0) {
    plotLaneLine(percetion_lines[0], "r-");
  }
  // 绘制右车道线
  if (percetion_lines[1].getID() != 0) {
    std::vector<float> x, y;
    plotLaneLine(percetion_lines[1], "b-");
  }
  // 绘制左左车道线
  if (percetion_lines[2].getID() != 0) {
    plotLaneLine(percetion_lines[2], "g-");
  }
  // 绘制右右车道线
  if (percetion_lines[3].getID() != 0) {
    plotLaneLine(percetion_lines[3], "y-");
  }

  // 绘制参考线
  if (ref_line.getID() != 0) {
    plotLaneLine(ref_line, "k--");
  }

  // 在右上角显示纵向加速度
  plt::text(80, 9,
            "Acceleration: " + std::to_string(acceleration_request) + " m/s^2");

  // 在右上角绘制方向盘转角
  float angle = steerwheel_request;
  float radius = 3.0;
  std::vector<float> arc_x, arc_y;
  int num_points = 100;
  for (int i = 0; i <= num_points; ++i) {
    float theta = angle * i / num_points;
    arc_x.push_back(90 + radius * std::cos(theta));
    arc_y.push_back(9 + radius * std::sin(theta));
  }
  std::string color = (angle >= 0) ? "red" : "blue";
  plt::plot(arc_x, arc_y, color);

  plt::pause(0.01);
}