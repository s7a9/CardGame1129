#ifndef GAMEUTILITIES_H
#define GAMEUTILITIES_H

#include <iostream>

// 光标移到指定位置输出
// 使用例：out(1,5) << “hello!”;
std::ostream& out(int line, int col);

// 清屏
void cls();

#endif //GAMEUTILITIES_H