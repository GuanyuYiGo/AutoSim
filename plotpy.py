import numpy as np
import matplotlib.pyplot as plt

# 定义多项式函数
def polynomial(x, a, b, c, d):
    return a + b * x + c * x**2 + d * x**3

# 指定起始点和终止点的 x 值
x_start = 0
x_end = 100

# 生成 x 数据
x = np.linspace(x_start, x_end, 400)

# 定义系数
coeffs1 = [2.96, 0.0234375, 0.000144596, -6.37e-07]
coeffs2 = [-0.78, 0.0292969, -9.77e-06, -4.84e-08]
coeffs3 = [-4.5, 0.0322266, -8.9884e-05, -1.56462e-07]

# 生成曲线数据
y1 = polynomial(x, *coeffs1)
y2 = polynomial(x, *coeffs2)
y3 = polynomial(x, *coeffs3)

# 计算第四条和第五条曲线的系数
coeffs4 = [(a + b) * 0.5 for a, b in zip(coeffs1, coeffs2)]
coeffs5 = [(a + b) * 0.5 for a, b in zip(coeffs2, coeffs3)]

# 生成第四条和第五条曲线的数据
y4 = polynomial(x, *coeffs4)
y5 = polynomial(x, *coeffs5)

# 绘制曲线
plt.plot(x, y1, label='Curve 1')
plt.plot(x, y2, label='Curve 2')
plt.plot(x, y3, label='Curve 3')
plt.plot(x, y4, linestyle='--', label='Curve 4 (dashed)')
plt.plot(x, y5, linestyle='--', label='Curve 5 (dashed)')

# 添加图例
plt.legend()

# 显示图形
plt.show()