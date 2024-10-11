#include <graphics.h> // 引入easyX图形库
#inc
int main(int argc, char** argv)
{
    // 初始化图形界面
    initgraph(800, 600); // 设置窗口大小为800x600

    // 加载图片
    IMAGE *img = LoadImage("background.jpg"); // 假设背景图片名为background.jpg

    if (img == NULL) {
        printf("Failed to load image.\n");
        return -1;
    }

    // 渲染图片
    PutImage(0, 0, img); // 在坐标(0, 0)开始绘制图片

    // 显示图片
    while (1) {
        display(); // 刷新显示
        if (kbhit()) { // 检测键盘输入
            getch();
            break; // 按任意键退出
        }
    }

    // 释放资源
    FreeImage(img);
    closegraph(); // 关闭图形界面

    return 0;
}

