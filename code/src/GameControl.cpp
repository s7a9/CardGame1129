#include "GameControl.h"
#include "GameIO.h"

using namespace std;

game_status_t game_status;

const card_t player_inital_cards[] = {
    {ct_attack, 2, 0}, {ct_attack, 2, 0}, {ct_attack, 2, 0}, 
};

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
    const char* enemy_level_options[] = {"相同等级"};
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
