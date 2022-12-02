#ifndef GAMEIO_H
#define GAMEIO_H

#include "PlayerDef.h"

// 展示标题画面
void DisplayTitle(game_status_t& status);

// 打印全部信息
void DisplayInfo(game_status_t& game_status);

// 打印玩家信息
void DisplayPlayerInfo(player_t& info); 

// 打印电脑信息
void DisplayEnemyInfo(player_t& info); 

// 让用户做选择，列出每个选项的信息
// options：字符串的数组，每个选项的文字
// n_choice：选项的个数
int MakeAChoice(const char* options[], int n_choice);

// 让用户做选择，只有一条说明
// hint：该选择的提示
// n_choice：选项的个数
int MakeAChoice(const char* hint, int n_choice);

// 展示玩家操作
void DisplayPlayerMove(int type);

// 展示电脑操作
void DisplayEnemyMove(int type);

// 展示一张牌
void DisplayCard(card_t& card);

#endif //GAMEIO_H