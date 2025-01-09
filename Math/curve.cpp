#include "curve.h"

// 求解二次方程的函数
bool solveQuadratic(float a, float b, float c, std::vector<float> &roots) {
  const float epsilon = 1e-6; // 设置一个小的阈值

  if (std::abs(a) < epsilon) {
    // 处理 a 接近 0 的情况，退化为一次方程 bx + c = 0
    if (std::abs(b) < epsilon) {
      // 如果 b 也接近 0，则无解
      return false;
    } else {
      // 一次方程 bx + c = 0 的解
      roots.push_back(-c / b);
      return true;
    }
  }
  float discriminant = b * b - 4 * a * c;
  if (discriminant > 0) {
    roots.push_back((-b + std::sqrt(discriminant)) / (2 * a));
    roots.push_back((-b - std::sqrt(discriminant)) / (2 * a));
  } else if (discriminant == 0) {
    roots.push_back(-b / (2 * a));
  } else {
    // 无实数根
    return false;
  }
  return true;
}

bool solveCubic(float a, float b, float c, float d, std::vector<float> &roots) {
  const float epsilon = 1e-6; // 设置一个小的阈值

  if (std::abs(a) < epsilon) {
    // 处理 a == 0 的情况，退化为二次方程
    return solveQuadratic(b, c, d, roots);
  }

  // 计算 delta0 和 delta1
  float delta0 = b * b - 3 * a * c;
  float delta1 = 2 * b * b * b - 9 * a * b * c + 27 * a * a * d;

  // 计算判别式
  float discriminant = delta1 * delta1 - 4 * delta0 * delta0 * delta0;

  // 计算 C
  std::complex<float> C = std::pow(
      std::complex<float>(
          (delta1 + std::sqrt(std::complex<float>(discriminant))) / 2.0f),
      1.0f / 3.0f);

  // 定义 omega1 和 omega2
  std::complex<float> omega1(-0.5, std::sqrt(3.0f) / 2.0f);
  std::complex<float> omega2(-0.5, -std::sqrt(3.0f) / 2.0f);

  // 计算三个根
  std::complex<float> root1 = -1.0f / (3.0f * a) * (b + C + delta0 / C);
  std::complex<float> root2 =
      -1.0f / (3.0f * a) * (b + omega1 * C + delta0 / (omega1 * C));
  std::complex<float> root3 =
      -1.0f / (3.0f * a) * (b + omega2 * C + delta0 / (omega2 * C));

  // 只保留实数部分
  if (std::abs(root1.imag()) < epsilon)
    roots.push_back(root1.real());
  if (std::abs(root2.imag()) < epsilon)
    roots.push_back(root2.real());
  if (std::abs(root3.imag()) < epsilon)
    roots.push_back(root3.real());

  return !roots.empty();
}

bool fitCubicPoly(const std::vector<Point> &points, std::vector<float> &coef,
                  const Point &origin) {

  if (points.size() < 4) {
    return false;
  }

  // 构建矩阵 A 和向量 B
  std::array<std::array<float, 4>, 4> A = {0};
  std::array<float, 4> B = {0};

  for (const auto &point : points) {
    float x = point.x;
    float y = point.y;
    float x2 = x * x;
    float x3 = x2 * x;
    float x4 = x3 * x;
    float x5 = x4 * x;
    float x6 = x5 * x;

    A[0][0] += 1;
    A[0][1] += x;
    A[0][2] += x2;
    A[0][3] += x3;
    A[1][1] += x2;
    A[1][2] += x3;
    A[1][3] += x4;
    A[2][2] += x4;
    A[2][3] += x5;
    A[3][3] += x6;

    B[0] += y;
    B[1] += y * x;
    B[2] += y * x2;
    B[3] += y * x3;
  }

  // 对称矩阵补全
  A[1][0] = A[0][1];
  A[2][0] = A[0][2];
  A[2][1] = A[1][2];
  A[3][0] = A[0][3];
  A[3][1] = A[1][3];
  A[3][2] = A[2][3];

  // 使用高斯消元法求解线性方程组 A * coef = B
  for (int i = 0; i < 4; ++i) {
    // 寻找主元
    int maxRow = i;
    for (int k = i + 1; k < 4; ++k) {
      if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
        maxRow = k;
      }
    }

    // 交换行
    std::swap(A[i], A[maxRow]);
    std::swap(B[i], B[maxRow]);

    // 消元
    for (int k = i + 1; k < 4; ++k) {
      float factor = A[k][i] / A[i][i];
      for (int j = i; j < 4; ++j) {
        A[k][j] -= factor * A[i][j];
      }
      B[k] -= factor * B[i];
    }
  }

  // 回代求解
  coef.resize(4);
  for (int i = 3; i >= 0; --i) {
    coef[i] = B[i] / A[i][i];
    for (int k = i - 1; k >= 0; --k) {
      B[k] -= A[k][i] * coef[i];
    }
  }

  return true;
}