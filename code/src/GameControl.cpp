#include "GameControl.h"
#include "GameIO.h"
#include "GameUtilities.h"

using namespace std;

game_status_t game_status;

const card_t player_inital_cards[] = {
    {ct_attack, 2, 0}, {ct_attack, 2, 0}, {ct_attack, 2, 0}, 
    {ct_defense, 2, 1}, {ct_poison, 2, 1}, {ct_pierce, 2, 2},
    {ct_heal, 2, 1}, {ct_putrefy, 0, 2}
};

const size_t player_inital_cards_n = sizeof(player_inital_cards) / sizeof(card_t);

inline int get_hp_by_level(int level) {
    return 10 + 5 * level;
}

inline int get_max_hand_by_level(int level) {
    return min(10, 1 + level);
}

card_t GetNewCard(int type, int level) {
    // 每种卡牌对应的行动点花费
    const int type_ap_cost[] = {0, 1, 1, 2, 2, 1, 2, 2, 2, 2};
    // 每种卡牌对应的基础值
    const int type_basic_value[] = {0, 3, 1, 2, 2, 2, 0, 1, 1, 0};
    return Card(type, type_basic_value[type] + level, type_ap_cost[type]);
}

// 生成电脑，暂定复制玩家的牌组
inline void SpawnEnemy() {
    game_status.enemy.bag_cards.Clear();
    int n = game_status.player.bag_cards.Size(), choice;
    const char* enemy_level_options[] = {"低一级", "相同等级", "高一级"};
    cls();
    out(10, 5) << "您的等级是" << game_status.player.level;
    out(11, 5) << "下一步想要挑战敌人的难度是：";
    choice = MakeAChoice(enemy_level_options, 3);
    game_status.enemy.level = max(1, game_status.player.level + choice - 2);
    for (int i = 0; i < n; i++) {
        game_status.enemy.bag_cards.Add(game_status.player.bag_cards[i]);
    }
    game_status.enemy.max_hp = game_status.enemy.health_point = 
        get_hp_by_level(game_status.enemy.level);
    game_status.enemy.poison_point = game_status.enemy.defense_point = 0;
    game_status.enemy.action_point = 0;
}

// 夺取电脑卡牌
void GetEnemyCard() {
    CardList& ecl = game_status.enemy.bag_cards;
    int n = game_status.enemy.hand_cards.Size();
    while (n--) {
        ecl.Add(game_status.enemy.hand_cards[0]);
        game_status.enemy.hand_cards.Remove(0);
    }
    if (ecl.Size() == 0) return;
    cls();
    out(5, 20) << "你可以夺取敌人的一张牌：";
    n = ecl.Size();
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) pos(7 + i / 2, 5);
        cout << i + 1 << ')';
        DisplayCard(ecl[i]);
        cout << '\t';
    }
    int choice = MakeAChoice("输入卡牌的编号,输入0跳过:", n);
    if (choice == 0) return;
    cls();
    out(10, 20) << "您夺取了：";
    pos(12, 20); DisplayCard(ecl[choice - 1]);
    out(14, 20) << "按任意键继续...";
    game_status.player.bag_cards.Add(ecl[choice - 1]);
    pause();
}

void RunGame() {
    InitIO();
    cls();
    for (int i = 0; i < player_inital_cards_n; ++i) {
        game_status.player.bag_cards.Add(player_inital_cards[i]);
    }
    game_status.player.level = 1;
    game_status.player.max_hp = game_status.player.health_point = get_hp_by_level(1);
    while (true) {
        // Fight()
        // 如果HandleResult返回0 显示退出信息+退出
        // Shopping()
        Fight();
        if (HandleResult() == 0) return;
        tidy_cards(game_status.player);
        tidy_cards(game_status.enemy);
        GetEnemyCard();
        Shopping();
        game_status.win_cnt++;
    }
}

void Fight() {
    // 初始化 game_status：洗牌、重置血量
    int choice;
    SpawnEnemy();
    game_status.player.bag_cards.Shuffle();
    game_status.enemy.bag_cards.Shuffle();
    game_status.turn = 1;
    draw_a_card(&game_status.player); draw_a_card(&game_status.player);
    draw_a_card(&game_status.enemy); draw_a_card(&game_status.enemy);
    game_status.player.defense_point = game_status.player.poison_point = 0;
    game_status.player.action_point = game_status.enemy.action_point = 0;
    while (true) {
        player_t* p;
        // 玩家回合 发牌、计算效果
        prepare_turn(p = &(game_status.player));
        if (p->health_point <= 0) return;
        while (true) { // 出牌
            choice = PlayerMove();
            if (choice == 0) break;
            choice--;
            if (p->hand_cards[choice].ap_cost >= 0)
                p->used_cards.Add(p->hand_cards[choice]);
            p->hand_cards.Remove(choice);
            // 血量<=0寄
            if (game_status.enemy.health_point <= 0) return;
        }
        p->action_point = 0;
        // 电脑回合 发牌、计算效果
        prepare_turn(p = &(game_status.enemy));
        if (p->health_point <= 0) return;
        while (true) {
            choice = EnemyMove();
            if (choice == 0) break;
            choice--;
            if (p->hand_cards[choice].ap_cost >= 0)
                p->used_cards.Add(p->hand_cards[choice]);
            p->hand_cards.Remove(choice);
            // 血量<=0寄
            if (game_status.enemy.health_point <= 0) return;
        }
        p->action_point = 0;
    }
}

int HandleResult() {
    static int cost=20;
    int choice_rebirth;
    const char *options="复活请输入1 原地去世请输入0: ";
    if (game_status.enemy.health_point<=0){
        game_status.money += game_status.enemy.level * 10 + 10;
        return 6;
    }
    else if (game_status.player.health_point<=0){
        cls();
        pos(15, 20);
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
                game_status.player.health_point=get_hp_by_level(game_status.player.level);
                game_status.money-=cost;
                cost*=2;
                return 1;
            }
        }
    }
    // 看看谁的血量<=0
    // 使用一定金币复活
    // 可以定义static int cost; 让复活需要的金币递增
    return 0;
}

void Shopping() {
    // 随机三张卡牌/升级
    static int ope_card_cost[3] = {2, 2, 20};
    card_t Ncard[3];
    int card_cost[3];
    bool bought[10] = {0};
    player_t& player = game_status.player;
    int choice, n;
    Ncard[0] = GetNewCard(rand() % 3 + 1, player.level);
    Ncard[1] = GetNewCard(rand() % 3 + 4, player.level);
    Ncard[2] = GetNewCard(rand() % 3 + 7, player.level);
    card_cost[0] = 5 + 5 * (player.level) / 2;
    card_cost[1] = 10 + 5 * (player.level) / 2;
    card_cost[2] = 15 + 5 * (player.level) / 2;
    int gift_opt = rand() % gift_n;
    while (true) {
        cls();
        out(5, 5) << "你遇到了小贩，他开出的条件是：";
        out(7, 10) << "1) "; DisplayCard(Ncard[0]); cout << "\t花费:" << card_cost[0];
        out(8, 10) << "2) "; DisplayCard(Ncard[1]); cout << "\t花费:" << card_cost[1];
        out(9, 10) << "3) "; DisplayCard(Ncard[2]); cout << "\t花费:" << card_cost[2];
        out(10, 10) << "4) 角色升一级\t花费:" << player.level * 5;
        out(11, 10) << "5) 删除一张卡牌\t花费:" << ope_card_cost[0];
        out(12, 10) << "6) 升级一张卡牌\t花费:" << ope_card_cost[1];
        out(13, 10) << "7) 升级天赋: " << get_gift_name(gift_opt) << " Lv." <<
            player.gift_level[gift_opt] << "->Lv." << player.gift_level[gift_opt] + 1 <<
            "\t花费:" << ope_card_cost[2];
        out(15, 5) << "你现在拥有的金币数: " << yellow << game_status.money << white;
        choice = MakeAChoice("输入数字以选择,输入0离开商店:", 7);
        if (choice == 0) return;
        if (choice == '#') {
            game_status.money += 100;
            continue;
        }
        if (choice == 5 || choice == 6) {
            cls();
            out(5, 5) << "你的牌包如下,升级需要" << ope_card_cost[1] << ",删除需要" << ope_card_cost[0];
            n = player.bag_cards.Size();
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) pos(7 + i / 2, 5);
                cout << i + 1 << ')';
                DisplayCard(player.bag_cards[i]);
                cout << '\t';
            }
            choice -= 5;
            int choice2 = MakeAChoice((choice == 0) ? "输入要删除的卡牌编号,0退出:" : "输入要升级的卡牌编号,0退出:", n);
            if (choice2 == 0) continue;
            if (game_status.money < ope_card_cost[choice]) {
                out(0, 0) << red << "金币不足!" << white;
                pause();
                continue;
            }
            choice2--;
            game_status.money -= ope_card_cost[choice];
            ope_card_cost[choice] += 2;
            cls();
            out(15, 10) << ((choice == 0) ? ("您移除了:") : ("卡牌升级为:")); 
            if (choice == 0) {
                DisplayCard(player.bag_cards[choice2]);
                player.bag_cards.Remove(choice2);
            }
            else {
                player.bag_cards[choice2] = 
                    GetNewCard(player.bag_cards[choice2].type, player.level);
                DisplayCard(player.bag_cards[choice2]);
            }
            pause();
        }
        else {
            if (bought[choice]) {
                out(0, 0) << red << "已经购买过这项物品!" <<white;
                pause();
                continue;
            }
            bought[choice] = true;
            choice--;
            switch (choice) {
            case 0: case 1: case 2: // 买卡
                if (game_status.money < card_cost[choice]) {
                    out(0, 0) << red << "金币不足!" << white;
                    pause();
                    break;
                }
                game_status.money -= card_cost[choice];
                cls();
                out(15, 10) << "您购买了:"; 
                DisplayCard(Ncard[choice]);
                pause();
                player.bag_cards.Add(Ncard[choice]);
                break;
            case 3: // 升级
                if (game_status.money < player.level * 5) {
                    out(0, 0) << red << "金币不足!" << white;
                    pause();
                    break;
                }
                game_status.money -= player.level * 5;
                player.level++;
                player.health_point = player.max_hp = get_hp_by_level(player.level);
                cls();
                out(15, 10) << "您升级了！"; 
                pause();
                break;
            case 6: // 天赋
                if (game_status.money < ope_card_cost[2]) {
                    out(0, 0) << red << "金币不足!" << white;
                    pause();
                    break;
                }
                game_status.money -= ope_card_cost[2];
                player.gift_level[gift_opt]++;
                ope_card_cost[2] += 10;
                cls();
                out(15, 10) << "天赋 " << get_gift_name(gift_opt) << 
                    " 升级为Lv." << player.gift_level[gift_opt];
                pause();
                break;
            }
        }
    }
}

int PlayerMove() {
    int choice,n=game_status.player.hand_cards.Size();
    DisplayInfo(game_status);
    while (true) {
        choice=MakeAChoice ("输入你想打出的牌,输入0结束出牌",n);
        if (choice==0) return 0;
        else if (choice == '#') {
            game_status.enemy.health_point = 0;
            return 0;
        }
        if (game_status.player.hand_cards[choice - 1].ap_cost <= game_status.player.action_point)
            break;
        out(0, 0) << red << "行动力不足!" << white;
    }
    DisplayPlayerMove(game_status.player.hand_cards[choice - 1].type);
    PlayCard(game_status.player.hand_cards[choice -1],game_status.player , game_status.enemy) ;
    return choice;
}

int EnemyMove() {
    // 电脑自动选择
    player_t& enemy = game_status.enemy;
    int n = enemy.hand_cards.Size();
    if (n == 0) return 0;
    for (int i = 0; i < n; ++i) {
        if (enemy.hand_cards[i].ap_cost <= enemy.action_point) {
            PlayCard(game_status.enemy.hand_cards[i], game_status.enemy, game_status.player);
            DisplayEnemyMove(game_status.enemy.hand_cards[i].type);
            pause();
            DisplayInfo(game_status);
            return i + 1;
        }
    }
    return 0;
}
