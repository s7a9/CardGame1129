#include "GameControl.h"
#include "GameIO.h"
#include "GameUtilities.h"

using namespace std;

game_status_t game_status;

const card_t player_inital_cards[] = {
    {ct_attack, 2, 0}, {ct_attack, 2, 0}, {ct_attack, 2, 0}, 
};

int get_hp_by_level(int level) {
    return 10 + 5 * level;
}

int get_max_hand_by_level() {
    
}

card_t GetNewCard(card_type_t type, int level) {
    // 每种卡牌对应的行动点花费
    const int type_ap_cost[] = {0, 1, 1, 2, 2, 1, 2, 2, 2, 2};
    // 每种卡牌对应的基础值
    const int type_basic_value[] = {0, 3, 1, 2, 2, 2, 0, 1, 1, 0};
    return Card(type, type_basic_value[type] + level, type_ap_cost[type]);
}

void SpawnEnemyCardBag() {
}

void RunGame() {
    while (false) {
        // Fight()
        // 如果HandleResult返回0 显示退出信息+退出
        // Shopping()
        Fight();
        if (HandleResult() == 0) return;
        Shopping();
    }
}

void Fight() {
    // 初始化 game_status：洗牌、重置血量
    int choice;
    char* enemy_level_options[] = {"低一级", "相同等级", "高一级"};
    choice = MakeAChoice(enemy_level_options, 3);
    switch (choice) {
    case 1:
        game_status.enemy.level = max(1, game_status.player.level - 1);
        break;
    case 3:
        game_status.enemy.level = game_status.player.level + 1;
        break;
    default:
        game_status.enemy.level = game_status.player.level;
        break;
    }
    SpawnEnemyCardBag();
    while (true) {
        // 玩家回合 发牌、计算效果

        while (true) {
            // 玩家打牌
            
        }
        // 血量<=0寄

        // 电脑回合 发牌、计算效果
        while (true) {
            // 电脑打牌
        }
        // 血量<=0寄
    }
}

int HandleResult() {
    // 看看谁的血量<=0
    // 使用一定金币复活
    // 可以定义static int cost; 让复活需要的金币递增
}

void Shopping() {
    // 随机三张卡牌/升级
    // 让玩家选择
}

int PlayerMove() {
    // 让玩家选择
}

int EnemyMove() {
    // 电脑自动选择
}
