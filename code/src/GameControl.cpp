#include "GameControl.h"
#include "GameIO.h"
#include "GameUtilities.h"

using namespace std;

game_status_t game_status;

const card_t player_inital_cards[] = {
    {ct_attack, 2, 0}, {ct_attack, 2, 0}, {ct_attack, 2, 0}, 
};

const size_t player_inital_cards_n = sizeof(player_inital_cards) / sizeof(card_t);

int get_hp_by_level(int level) {
    return 10 + 5 * level;
}

int get_max_hand_by_level(int level) {
    return min(10, 1 + level);
}

card_t GetNewCard(card_type_t type, int level) {
    // 每种卡牌对应的行动点花费
    const int type_ap_cost[] = {0, 1, 1, 2, 2, 1, 2, 2, 2, 2};
    // 每种卡牌对应的基础值
    const int type_basic_value[] = {0, 3, 1, 2, 2, 2, 0, 1, 1, 0};
    return Card(type, type_basic_value[type] + level, type_ap_cost[type]);
}

// 生成电脑的牌组，暂定复制玩家的牌组
void SpawnEnemyCardBag() {
    int n = game_status.player.bag_cards.Size();
    for (int i = 0; i < n; i++) {
        game_status.enemy.bag_cards.Add(game_status.player.bag_cards[i]);
    }
}

void RunGame() {
    for (int i = 0; i < player_inital_cards_n; ++i) {
        game_status.player.bag_cards.Add(player_inital_cards[i]);
    }
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
    game_status.enemy.level = max(1, game_status.player.level + choice - 2);
    SpawnEnemyCardBag();
    player_t* p;
    while (true) {
        // 玩家回合 发牌、计算效果
        p = &(game_status.player);
        int draw_cards_n = 2 + p->level / 2;
        for (int i = 0; p->bag_cards.Size() && i < draw_cards_n; ++i) {
            p->hand_cards.Add(p->bag_cards[0]);
            p->bag_cards.Remove(0);
        }
        p->defense_point -= p->poison_point;
        p->poison_point--;
        p->health_point -= p->defense_point;
        if (p->health_point <= 0) return;
        p->action_point += 1 + p->level / 2;
        p->action_point = max(p->action_point, 0);
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
