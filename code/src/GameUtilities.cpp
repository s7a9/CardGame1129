#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "GameUtilities.h"

using namespace std;

console_color_t color(int text_color, int back_color) {
    return (console_color_t){text_color, back_color};
}

std::ostream& operator<<(std::ostream& out, console_color_t clr) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    unsigned short wAttributes = ((unsigned)(clr.bc << 4)) | ((unsigned)(clr.tc));
    SetConsoleTextAttribute(hStdOut, wAttributes);
    return out;
}

int pause() {
    return getch();
}

void pos(int line, int col) {
    COORD p;
    p.X = line, p.Y = col;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

std::ostream& out(int line, int col) {
    pos(line, col);
    return cout;
}

void cls() {
    system("cls");
}