#ifndef CARDACTIONS_H
#define CARDACTIONS_H

#include "PlayerDef.h"

// 打出一张牌，执行这张牌造成的影响
// 注意p1 p2是引用
void PlayCard(card_t card, player_t& p1, player_t& p2);

#endif //CARDACTIONS_H