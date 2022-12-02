#include "CardActions.h"

using namespace std;

void PlayCard(card_t card, player_t& p1, player_t& p2) {
    // switch-case 施加卡牌的效果
    if (p1.action_point < card.ap_cost) return;
        else p1.action_point -= card.ap_cost;
    int idx;
    switch (card.type)
    {
        case ct_null: return; break;
        case ct_attack: 
            if (p2.defense_point >= card.value) p2.defense_point -= card.value;
                else {p2.health_point -= (card.value - p2.defense_point); p2.defense_point = 0;}
            break;
        case ct_defense: p1.defense_point += card.value; break;
        case ct_poison: p2.poison_point += card.value; break;
        case ct_pierce: p2.health_point -= card.value; break;
        case ct_heal: p1.health_point = min(p1.max_hp, p1.health_point + card.value); break;
        case ct_putrefy: p1.poison_point = 0; break;
        case ct_spawn:
            for (int i = 1; i <= card.value && p1.bag_cards.Size(); i++)
            {
                idx = p1.bag_cards.Size() - 1;
                p1.hand_cards.Add(p1.bag_cards[idx]);
                p1.bag_cards.Remove(idx);
            }
            break;
        case ct_steal:
            if (p2.hand_cards.Size() == 0) break;
            idx = p2.hand_cards.Size() - 1;
            p1.hand_cards.Add(p2.hand_cards[idx]);
            p2.hand_cards.Remove(idx);
            break;
        case ct_fatigue: p2.action_point -= card.value; break;
        default: break;
    }
    return;
}