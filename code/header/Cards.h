#ifndef CARDS_H
#define CARDS_H

#include <vector>

#define ct_null 0
#define ct_attack 1
#define ct_defense 2
#define ct_poison 3
#define ct_pierce 4
#define ct_heal 5
#define ct_putrefy 6
#define ct_spawn 7
#define ct_steal 8
#define ct_fatigue 9

const char* get_card_name(int i);

struct card_t { // 卡牌结构体
    int type; // 卡牌类型
    int value; // 卡牌的值
    int ap_cost; // 卡牌消耗的行动点
};

class CardList { // 牌堆管理器，可以加入、删除元素的牌数组
public:
    // 加入一张牌到牌堆最后
    void Add(card_t item); 

    // 加入多张牌到牌堆最后
    void AddCards(card_t items[], int n);

    // 删除指定下标的一张牌
    void Remove(int index); 

    // 删除和传入牌相同的一张牌
    void Remove(card_t card); 

    // 获取指定下标的一张牌
    card_t& Get(int index); 

    // 获取指定下标的一张牌
    card_t& operator[](int index); 

    // 获取牌堆大小
    int Size() const; 

    // 洗牌
    void Shuffle();

    // 清除全部
    void Clear();

private:
    std::vector<card_t> cards;
};

// 生成一张新牌
card_t Card(int type, int value, int cost);

#endif //CARDS_H