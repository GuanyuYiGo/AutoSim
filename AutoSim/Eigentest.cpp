#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <vector>

// 求解一元三次方程
std::vector<double> solveCubic(double a, double b, double c, double d) {
  std::vector<double> roots;

  // 构建伴随矩阵
  Eigen::Matrix3d companion;
  companion << 0, 0, -d / a, 1, 0, -c / a, 0, 1, -b / a;

  // 求解特征值
  Eigen::EigenSolver<Eigen::Matrix3d> solver(companion);
  Eigen::VectorXcd eigenvalues = solver.eigenvalues();

  // 获取实数根
  for (int i = 0; i < eigenvalues.size(); ++i) {
    if (eigenvalues[i].imag() == 0) { // 只考虑实数根
      roots.push_back(eigenvalues[i].real());
    }
  }

  return roots;
}

int main() {
  // 示例：求解 x^3 - 6x^2 + 11x - 6 = 0
  double a = 1;
  double b = -6;
  double c = 11;
  double d = -6;

  std::vector<double> roots = solveCubic(a, b, c, d);

  std::cout << "Roots: ";
  for (double root : roots) {
    std::cout << root << " ";
  }
  std::cout << std::endl;
  system("pause");
  return 0;
}