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
    static int cost=20;
    int choice_rebirth;
    char *options="复活请输入1 原地去世请输入0";
    if (game_status.enemy.health_point<=0)
        return 6;
    else if (game_status.player.health_point<=0){
        if (game_status.money<cost) {
            cout<<"穷光蛋，你输了！！！"<<endl;
            return 0;
        }
        else {
            cout << "所需要的金币为：" << cost <<"你拥有的金币为" << game_status.money;
            choice_rebirth=MakeAChoice(options,1);
            
            if (choice_rebirth==0) {
                cout <<"你输了！！！"<<endl;
                 return 0;
            }
            if (choice_rebirth==1) {
                cls();
                cout <<"按任意键继续游戏"<<endl; 
                pause();
                game_status.player.healt_point=get_hp_by_level(game_status.player.level);
                game_status.money-=cost;
                cost*=2;
                return 1;
            }
        }
        
    }
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
        int choiceNcard0 = MakeAChoice(choices, 4);
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
    char*player_choice="输入你想打出的牌,输入0结束出牌";
    int choice,n=game_status.player.hand_cards.Size();
    
    choice=MakeAChioce (player_chioce,n);
    if (choice==0) return 0;
    else PlayCard(game_status.player.hand_cards[choice -1],game_status.player , game_status.enemy) ;
         // 让玩家选择
}

int EnemyMove() {
    // 电脑自动选择
}
