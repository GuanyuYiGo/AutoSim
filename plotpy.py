import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# 创建数据
theta = np.linspace(0, 2 * np.pi, 100)
z = np.linspace(0, 1, 100)
theta, z = np.meshgrid(theta, z)
x = np.cos(theta)
y = np.sin(theta)

# 创建图形
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 绘制圆柱
ax.plot_surface(x, y, z, color='b')

# 设置标签
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# 显示图形
plt.show()