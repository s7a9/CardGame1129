#ifndef PLAYERDEF_H
#define PLAYERDEF_H

#include "Cards.h"

// 打牌者结构体
struct player_t {
    int health_point; // 血量
    int action_point; // 行动点
    int poison_point; // 毒性
    int defense_point; // 盾
    int fatigue_point;  // 疲劳
    int level; // 等级
    CardList hand_cards; // 手牌数组
    CardList bag_cards; // 牌库数组
};

// 游戏信息结构体
struct game_status_t {
    int money; // 玩家的金钱数
    player_t player, enemy;
};

#endif //PLAYERDEF_H