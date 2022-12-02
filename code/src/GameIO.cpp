#include <cctype>
#include "GameIO.h"
#include "GameUtilities.h"
#include <iostream>
using namespace std;

void DisplayInfo(game_status_t& game_status) {
    cls();
    // 打印玩家金币数 回合数 等等信息
    out(1,55)<<white<<"第"<<game_status.turn<<"轮";
    out(2,5)<<yellow<<"金币:"<<white<<game_status.money;
    // 调用下面的两个函数
    DisplayPlayerInfo(game_status.player);
    DisplayEnemyInfo(game_status.enemy);
}

void DisplayPlayerInfo(player_t& info) {
    // 打印血量、手牌等等战斗信息
    out(5,5)<<"急着打败魔王就回老家结婚的勇者";
    int i, t;
    out(6,5)<<white<<"level"<<info.level<<".";
    out(7,5)<<red<<"血量"<<white<<info.health_point<<'/'<<info.max_hp;
    t = info.health_point * 10 / info.max_hp;
    for(i=0;i<t;i++) cout<<"❤️";
    out(8,5)<<blue<<"行动点"<<white<<info.action_point;
    for(i=0;i<info.action_point;i++) cout<<"💪";
    out(9,5)<<green<<"毒性"<<white<<info.poison_point;
    for(i=0;i<info.poison_point;i++) cout<<"🤢";
    out(10,5)<<yellow<<"盾"<<white<<info.defense_point;
    for(i=0;i<info.defense_point;i++) cout<<"🛡️";
    int n = info.hand_cards.Size();
    cout<<endl<<endl;
    for(int i=0;i<n;i++){
        card_t& card = info.hand_cards[i];
        cout<<"卡牌"<<i+1<<':';
        DisplayCard(info.hand_cards[i]);
        cout << endl;
    }
}

void DisplayEnemyInfo(player_t& info) {
    // 打印血量、手牌等等战斗信息
    out(5,65)<<"没钱随份子所以要全力阻止勇者的魔王";
    int i,t;
    out(6,65)<<white<<"level"<<info.level<<".";
    out(7,65)<<red<<"血量"<<white<<info.health_point<<'/'<<info.max_hp;
    t = info.health_point * 10 / info.max_hp;
    for(i=0;i<t;i++) cout<<"❤️";
    out(8,65)<<blue<<"行动点"<<white<<info.action_point;
    for(i=0;i<info.action_point;i++) cout<<"💪";
    out(9,65)<<green<<"毒性"<<white<<info.poison_point;
    for(i=0;i<info.poison_point;i++) cout<<"🤢";
    out(10,65)<<yellow<<"盾"<<white<<info.defense_point;
    for(i=0;i<info.defense_point;i++) cout<<"🛡️";
    int n = info.hand_cards.Size();
    for(i=0;i<n;i++){
        out(i+12,60)<<"卡牌"<<i+1<<":???";
    }
}


int MakeAChoice(const char* options[], int n_choice) {
    // 让用户选择
    int n=n_choice;
    int i=0;
    pos(25,5);
    for(i=0;n-i>0;){
        for(int j=0;j<4&&n>i;j++,i++){
            cout<<(char)('A'+i)<<": "<<options[i];
        }
        cout<<endl;
    }
    cout<<"请键入你的选择，若选择跳过请键入0";
    char ch;
    while(1){
        ch = pause();
        if (ch == '0') return 0;
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == '@') exit(0);
            if (ch - 'A' < n_choice) {
                cout << endl << "您的选择是" << ch << ":" << options[ch-'A'] << ",按任意键继续...";
                pause();
                return ch - 'A' + 1;
            }
        }
        cout << endl <<"您的选择不存在！请重新选择:";
    }
    return 0;
}

int MakeAChoice(const char* hint, int n_choice) {
    // 让用户选择
    pos(25,5);
    cout<<hint;
    int n;
    while(1){
        n = pause() - '0';
        if (n == '@' - '0') exit(0);
        if(n >= 0 && n <= n_choice)break;
        else cout<<"请输入0到"<<n_choice<<"之间的数字!"<<endl;
    }
    return n;
}


void DisplayPlayerMove(int type) {
    cls();
    pos(10,45);
    switch (type)
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
}

void DisplayEnemyMove(int type) {
    pos(25, 5);
    cout << "                                ";
    pos(25, 5);
    switch (type)  
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
}

void DisplayCard(card_t& card) {
    cout << get_card_name(card.type) << "\t卡牌效能" << card.value << "🗡️"
        << "\t卡牌消耗" << card.ap_cost << "💪";
}