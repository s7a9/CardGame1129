#ifndef PLAYERDEF_H
#define PLAYERDEF_H

#include "Cards.h"

#define gift_drawallcards 0

// 打牌者结构体
struct player_t {
    int max_hp; // 最大血量
    int health_point; // 血量
    int action_point; // 行动点
    int poison_point; // 毒性
    int defense_point; // 盾
    int level; // 等级
    int gift_level[3]; // 天赋等级
    CardList hand_cards; // 手牌数组
    CardList bag_cards; // 牌库数组
    CardList used_cards; // 使用过的牌堆
};

// 游戏信息结构体
struct game_status_t {
    int money; // 玩家的金钱数
    int turn; // 回合数
    int win_cnt;
    player_t player, enemy;
};

void draw_a_card(player_t* p);

void prepare_turn(player_t* p);

void tidy_cards(player_t& p);

#endif //PLAYERDEF_H