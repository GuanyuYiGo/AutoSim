% filepath: /d:/OpenDrive/plot.m

% 创建数据
theta = linspace(0, 2 * pi, 100);
z = linspace(0, 1, 100);
[theta, z] = meshgrid(theta, z);
x = cos(theta);
y = sin(theta);

% 创建图形
figure;
ax = gca;
hold on;

% 绘制圆柱
h = surf(x, y, z, 'FaceColor', 'b', 'EdgeColor', 'none');

% 设置标签
xlabel('X');
ylabel('Y');
zlabel('Z');

% 设置轴范围
xlim([-2, 2]);
ylim([-2, 2]);
zlim([0, 1]);

% 动画参数
frames = 100;
offset = linspace(-1, 1, frames);

% 动画循环
for i = 1:frames
    % 更新圆柱的位置
    h.ZData = z + offset(i);

    % 更新图形
    drawnow;

    % 暂停以控制动画速度
    pause(0.05);
end

hold off;