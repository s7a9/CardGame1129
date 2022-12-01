#include <cctype>
#include "GameIO.h"
#include "GameUtilities.h"
#include <iostream>
using namespace std;

void DisplayInfo(game_status_t& game_status) {
    // 打印玩家金币数 回合数 等等信息
    out(1,55)<<white<<"第"<<game_status.turn<<"轮";
    out(2,5)<<yellow<<"金币:"<<white<<game_status.money;
    // 调用下面的两个函数
    DisplayPlayerInfo(game_status.player);
    DisplayEnemyInfo(game_status.enemy);
}

void DisplayPlayerInfo(player_t& info) {
    // 打印血量、手牌等等战斗信息
    int i;
    out(6,5)<<white<<"level"<<info.level<<".";
    out(7,5)<<red<<"血量"<<white<<info.health_point;
    for(i=0;i<info.health_point;i++) cout<<"❤️";
    out(8,5)<<blue<<"行动点"<<white<<info.action_point;
    for(i=0;i<info.health_point;i++) cout<<"💪";
    out(9,5)<<green<<"毒性"<<white<<info.poison_point;
    for(i=0;i<info.health_point;i++) cout<<"🤢";
    out(10,5)<<yellow<<"盾"<<white<<info.defense_point;
    for(i=0;i<info.health_point;i++) cout<<"🛡️";
    out(11,5)<<blue<<"疲惫"<<white<<info.fatigue_point;
    for(i=0;i<info.health_point;i++) cout<<"😴";
    int n = info.hand_cards.Size();
    cout<<endl;
    for(int i=0;i<n;i++){
        card_t& card = info.hand_cards[i];
        cout<<"卡牌"<<i+1<<":"<<card_type_names[card.type]<<endl;
        cout<<"卡牌效能"<<card.value<<"   ";
        for(int j=0;j<card.value;j++) cout<<"🗡️"<<endl;
        cout<<"卡牌消耗"<<card.ap_cost<<"   ";
        for(int j=0;j<card.ap_cost;j++) cout<<"💪"<<endl;

    }
}

void DisplayEnemyInfo(player_t& info) {
    // 打印血量、手牌等等战斗信息
    int i;
    out(6,65)<<white<<"level"<<info.level<<".";
    out(7,65)<<red<<"血量"<<white<<info.health_point;
    for(i=0;i<info.health_point;i++) cout<<"❤️";
    out(8,65)<<blue<<"行动点"<<white<<info.action_point;
    for(i=0;i<info.health_point;i++) cout<<"💪";
    out(9,65)<<green<<"毒性"<<white<<info.poison_point;
    for(i=0;i<info.health_point;i++) cout<<"🤢";
    out(10,65)<<yellow<<"盾"<<white<<info.defense_point;
    for(i=0;i<info.health_point;i++) cout<<"🛡️";
    out(11,65)<<blue<<"疲惫"<<white<<info.fatigue_point;
    for(i=0;i<info.health_point;i++) cout<<"😴";
    int n = info.hand_cards.Size();
    for(i=0;i<n;i++){
        out(i+12,60)<<"卡牌"<<i<<":???"<<endl;
    }
}


int MakeAChoice(char* options[], int n_choice) {
    // 让用户选择
    int n=n_choice;
    int i=0;
    pos(25,5);
    for(i=0;n-i>0;){
        for(int j=0;j<4&&n>i;j++,i++){
            cout<<'A'+i<<": "<<options[i];
        }
        cout<<endl;
    }
    cout<<"请键入你的选择，若选择跳过请键入0"<<endl;
    while(1){
        char ch = pause();
        if(ch==0) {break;}
        else if( ch-'A'+1>n_choice){
            cout<<"您的选择不存在！请重新选择"<<endl;
        }
        else if (isalpha(ch)) {
            ch = toupper(ch);
            break;
        }
    }
    if(ch=='0'){
        cout<<"您选择了跳过!"<<endl;
        return 0;
    }
    cout<<"您的选择是"<<ch<<":"<<options[ch-'A']<<endl;
    int w=(card_type_t)options[ch-'A'];
    if(w>=0&&w<=9){
        cls();
        pos(25,55);
    }
    switch (w)
    {
    case 1:cout<<red<<"接好了，这是我全力的一击！"<<endl<<white<<"对方受到了攻击！";break;
    case 2:cout<<yellow<<"啊，这是守护的力量！"<<endl<<white<<"您的护盾增加了！";break;
    case 3:cout<<green<<"看见了吗，这是我一路走来背负的罪恶啊。。。"<<endl<<white<<"对方中毒了！";break;
    case 4:cout<<red<<"我们都是如此脆弱啊"<<endl<<white<<"对方受到了穿刺攻击！";break;
    case 5:cout<<pink<<"感受到了哦，爱的力量"<<endl<<white<<"您的生命值恢复了！";break;
    case 6:cout<<blue<<"圣光啊，洗涤我身上的不详吧"<<endl<<white<<"您的负面效果被清除！";break;
    case 7:cout<<yellow<<"言已至此，感受无中生有的奇迹吧"<<endl<<white<<"您收获了新的卡牌！";break;
    case 8:cout<<green<<"你想到过被自己的力量伤害的一天吗？"<<endl<<white<<"您偷盗了对方的卡牌！";break;
    case 9:cout<<blue<<"别硬撑了，你其实很疲惫了吧"<<endl<<white<<"对方进入了疲惫！";break;
        /* code */
        break;
    
    default:
        break;
    }
    return ch-'A';
}

int MakeAChoice(char* hint, int n_choice) {
    // 让用户选择
    pos(25,5);
    cout<<hint;
    int n;
    while(1){
        n = pause();
        if(n>=0&&n<=n_choice)break;
        else cout<<"请输入0到"<<n_choice<<"之间的数字!"<<endl;
    }
    return n;
}