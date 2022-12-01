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

int get_hp_by_level(int level) {
    return 10 + 5 * level;
}

int get_max_hand_by_level(int level) {
    return min(10, 1 + level);
}

card_t GetNewCard(int type, int level) {
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
        Shopping();
    }
}

void prepare_turn(player_t* p) {
    int draw_cards_n = 2 + p->level / 2;
    for (int i = 0; p->bag_cards.Size() && i < draw_cards_n; ++i) {
        p->hand_cards.Add(p->bag_cards[0]);
        p->bag_cards.Remove(0);
    }
    p->defense_point -= p->poison_point;
    if (p->poison_point > 0) p->poison_point--;
    if (p->defense_point < 0) {
        p->health_point += p->defense_point;
        p->defense_point = 0;
    }
    if (p->health_point <= 0) return;
    p->action_point += 2 + p->level / 2;
    p->action_point = max(p->action_point, 0);
}

void Fight() {
    // 初始化 game_status：洗牌、重置血量
    int choice;
    const char* enemy_level_options[] = {"低一级", "相同等级", "高一级"};
    out(10, 5) << "您的等级是" << game_status.player.level;
    out(11, 5) << "下一步想要挑战敌人的难度是：";
    choice = MakeAChoice(enemy_level_options, 3);
    game_status.enemy.level = max(1, game_status.player.level + choice - 2);
    SpawnEnemyCardBag();
    game_status.enemy.max_hp = game_status.enemy.health_point = 
        get_hp_by_level(game_status.enemy.level);
    game_status.player.bag_cards.Shuffle();
    game_status.enemy.bag_cards.Shuffle();
    prepare_turn(&(game_status.player));
    prepare_turn(&(game_status.enemy));
    game_status.player.action_point = game_status.enemy.action_point = 0;
    game_status.turn = 1;
    while (true) {
        player_t* p;
        // 玩家回合 发牌、计算效果
        prepare_turn(p = &(game_status.player));
        if (p->health_point <= 0) return;
        while (true) { // 出牌
            choice = PlayerMove();
            if (choice == 0) break;
            choice--;
            p->bag_cards.Add(p->hand_cards[choice]);
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
            p->bag_cards.Add(p->hand_cards[choice]);
            p->hand_cards.Remove(choice);
            pause();
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

    card_t Ncard[3];
    player_t& player = game_status.player;
    srand((unsigned)time(NULL));
    for (int i = 0; i <= 2; i++) {
        Ncard[i] = GetNewCard((rand() % 10), player.level);
        cout << get_card_name(Ncard[i].type) << " 卡牌的值:" << Ncard[i].value << " 卡牌消耗的行动点:" << Ncard[i].ap_cost << endl;
    }
    const char* choices[5] = { "不选择","购买卡牌一(花5块钱)","购买卡牌二(花6块钱)","购买卡牌三(花7块钱)","等级+1(花6块钱)" };
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
    const char*player_choice="输入你想打出的牌,输入0结束出牌";
    int choice,n=game_status.player.hand_cards.Size();
    DisplayInfo(game_status);
    while (true) {
        choice=MakeAChoice (player_choice,n);
        if (choice==0) return 0;
        if (game_status.player.hand_cards[choice - 1].ap_cost <= game_status.player.action_point)
            break;
        out(0, 0) << "行动力不足!";
    }
    int w=game_status.player.hand_cards[choice - 1].type;
    cls();
    pos(10,45);
    switch (w)  
    {
        case 1:cout<<red<<"接好了，这是我全力的一击！"<<endl<<white<<"对方受到了攻击！";break;
        case 2:cout<<yellow<<"你是不会懂的，我们彼此守护的力量！"<<endl<<white<<"您的护盾增加了！";break;
        case 3:cout<<green<<"沾染上吧，这是我一路走来背负的罪恶啊。。。"<<endl<<white<<"对方中毒了！";break;
        case 4:{cout<<white<<"我啊，曾经也是一个人的盾牌呢";
            out(11,45)<<"可是啊，要是当时我守护住了就好了";
            out(12,45)<<red<<"轮到你来尝尝了，那种用尽全力却无法守护的痛啊啊啊啊"<<endl<<white<<"对方受到了穿刺攻击！";break;}
        case 5:cout<<pink<<"原来你一直在我身边治愈我啊，吾爱"<<endl<<white<<"您的生命值恢复了！";break;
        case 6:cout<<blue<<"圣光啊，洗涤我身上的不详吧"<<endl<<white<<"您的负面效果被清除！";break;
        case 7:cout<<yellow<<"言已至此，【made in heaven】"<<endl<<white<<"您收获了新的卡牌！";break;
        case 8:cout<<green<<"你想到过被自己的力量伤害的一天吗？"<<endl<<white<<"您偷盗了对方的卡牌！";break;
        case 9:cout<<blue<<"别硬撑了，你其实很疲惫了吧"<<endl<<white<<"对方受到了疲惫！";break;
    }
    out(15,5) << "任意键继续:";
    pause();
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
            DisplayInfo(game_status);
            pos(25, 5);
            switch (game_status.enemy.hand_cards[i].type)  
            {
                case 1:cout<<white<<"您受到了攻击！";break;
                case 2:cout<<white<<"对方的护盾增加了！";break;
                case 3:cout<<white<<"您中毒了！";break;
                case 4:cout<<white<<"您受到了穿刺攻击！";break;
                case 5:cout<<white<<"对方的生命值恢复了！";break;
                case 6:cout<<white<<"对方的负面效果被清除！";break;
                case 7:cout<<white<<"对方收获了新的卡牌！";break;
                case 8:cout<<white<<"对方偷盗了对方的卡牌！";break;
                case 9:cout<<white<<"您感到疲惫！";break;
            }
            return i + 1;
        }
    }
    return 0;
}
