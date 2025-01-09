#include "matplotlibcpp/matplotlibcpp.h"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace plt = matplotlibcpp;

int main() {
  py::scoped_interpreter guard{}; // 启动 Python 解释器

  // 准备数据
  std::vector<double> x = {1, 2, 3, 4, 5};
  std::vector<double> y = {1, 4, 9, 16, 25};

  // 绘制图表
  plt::plot(x, y);
  plt::show();

  return 0;
}