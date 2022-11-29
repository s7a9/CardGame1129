#ifndef CARDS_H
#define CARDS_H

enum card_type_t { // 卡牌类型
    ct_null, // 空卡牌
    ct_attack, // 普通攻击
    ct_defense, // 加盾
    ct_poison,  // 投毒
    ct_pierece, // 穿刺
    ct_heal, // 回复
    ct_putrefy, // 净化
    ct_spawn, // 无中生有
    ct_steal, // 顺手牵羊
    ct_fatigue, // 疲劳
};

struct card_t { // 卡牌结构体
    card_type_t type; // 卡牌类型
    int value; // 卡牌的值
    int ap_cost; // 卡牌消耗的行动点
};

class CardList { // 牌堆管理器，可以加入、删除元素的牌数组
public:
    // 加入一张牌到牌堆最后
    void Add(card_t item); 

    // 删除指定下标的一张牌
    void Remove(int index); 

    // 删除和传入牌相同的一张牌
    void Remove(card_t card); 

    // 获取指定下标的一张牌
    card_t& Get(int index) const; 

    // 获取指定下标的一张牌
    card_t& operator[](int index) const; 

    // 获取牌堆大小
    int Size() const; 

    // 洗牌
    void Shuffle();
};

// 生成一张新牌
card_t Card(card_type_t type, int value, int cost);

#endif //CARDS_H