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

    card_t Ncard[3];
    srand((unsigned)time(NULL));
    for (int i = 0; i <= 2; i++) {
        Ncard[i] = GetNewCard(rand() % 10, level);
        cout << card_type_names[Ncard[i].type] << ' 卡牌的值:' << Ncard[i].value << ' 卡牌消耗的行动点:' << Ncard[i].ap_cost << endl;
    }
    //0
    char* choices[5] = { "不选择","购买卡牌一(花5块钱)","购买卡牌二(花6块钱)","购买卡牌三(花7块钱)","等级+1(花6块钱)" };
    int choice_flag[5] = { 5,1,1,1,1 };
    int flag0 = 0;
    while (1) {
        cout << "你要买什么:";
        int choiceNcard0 = MakeAChoice(chioces, 4);
        switch (choiceNcard0) {
        case 0:
            if (choice_flag[choiceNcard0] > 0) {
                flag0 = 1; choice_flag[choiceNcard0]--;
            }
            else { break; }
            break;
        case 1:
            if (choice_flag[choiceNcard0] > 0 && game_status.money >= 5) {
                player.bag_cards.Add(Ncard[0]); game_status.money -= 5; choice_flag[choiceNcard0]--;
            }
            else { break; }
            break;
        case 2:
            if (choice_flag[choiceNcard0] > 0 && game_status.money >= 6) {
                player.bag_cards.Add(Ncard[1]); game_status.money -= 6; choice_flag[choiceNcard0]--;
            }
            else { break; }
            break;
        case 3:
            if (choice_flag[choiceNcard0] > 0 && game_status.money >= 7) {
                player.bag_cards.Add(Ncard[2]); game_status.money -= 7; choice_flag[choiceNcard0]--;
            }
            else { break; }
            break;
        case 4:
            if (choice_flag[choiceNcard0] > 0 && game_status.money >= 6) {
                player.level++; game_status.money -= 6; choice_flag[choiceNcard0]--;
            }
            else { break; }
            break;
        default: break;
        }
        if (flag0 == 1) { break; }
    }
}

int PlayerMove() {
    // 让玩家选择
}

int EnemyMove() {
    // 电脑自动选择
}
