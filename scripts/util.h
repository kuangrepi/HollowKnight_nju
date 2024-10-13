#include <graphics.h>
#include <random>

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
               GetImageHDC(img), 0, 0, w, h, {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}

inline int generate_random_number(int min, int max) {
    std::random_device rd;  // 用于生成种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 生成随机数
    std::uniform_int_distribution<> dis(min, max); // 定义范围

    return dis(gen); // 生成随机数
}