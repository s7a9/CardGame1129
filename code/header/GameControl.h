#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "CardActions.h"

// 游戏的进入点
void RunGame(); 

// 开始一场战斗
void Fight(); 

// 结算战斗
void HandleResult(); 

// 进入商店界面
void Shopping(); 

// 玩家选择出一张牌 0代表结束回合
int PlayerMove(); 

// 电脑选择出一张牌 0代表结束回合
int EnemyMove(); 

#endif //GAMECONTROL_H