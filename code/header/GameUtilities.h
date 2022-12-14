#ifndef GAMEUTILITIES_H
#define GAMEUTILITIES_H

#include <iostream>

// 颜色类型
struct console_color_t {
    int tc, bc;
};

// 获取自定义颜色
console_color_t color(int text_color, int back_color);

const console_color_t white = color(15, 0);

const console_color_t blue = color(9, 0);

const console_color_t red = color(12, 0);

const console_color_t green = color(10, 0);

const console_color_t yellow = color(14, 0);

const console_color_t pink = color(13, 0);

std::ostream& operator<<(std::ostream& out, console_color_t clr);

void InitIO();

// 暂停，按任意键继续
// 返回按下哪个键
int pause();

// 光标移到指定位置
void pos(int line, int col);

// 光标移到指定位置并输出
// 使用例：out(1,5) << “hello!”;
std::ostream& out(int line, int col);

// 清屏
void cls();

#endif //GAMEUTILITIES_H