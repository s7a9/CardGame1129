#include "PlayerDef.h"
#include <cstdlib>

using namespace std;

void draw_a_card(player_t* p) {
    if (p->bag_cards.Size()) {
        p->hand_cards.Add(p->bag_cards[0]);
        p->bag_cards.Remove(0);
    }
    else {
        if (p->gift_level[gift_lasthit]) {
            p->hand_cards.Add(Card(ct_attack, 
                p->used_cards.Size() * p->gift_level[gift_lasthit], -1));
        }
        p->bag_cards.AddCards(p->used_cards);
        p->used_cards.Clear();
        p->bag_cards.Shuffle();
    }
}

void prepare_turn(player_t* p) {
    int draw_cards_n = 2 + p->level / 2;
    if (p->gift_level[gift_autodefense]) {
        p->defense_point += p->gift_level[gift_autodefense];
    }
    for (int i = 0; i < draw_cards_n; ++i) {
        draw_a_card(p);
    }
    p->defense_point -= p->poison_point;
    if (p->poison_point > 0) p->poison_point--;
    if (p->defense_point < 0) {
        p->health_point += p->defense_point;
        p->defense_point = 0;
    }
    if (p->health_point <= 0) return;
    p->action_point += 2 + p->level;
    p->action_point = max(p->action_point, 0);
}

void tidy_cards(player_t& p) {
    p.bag_cards.AddCards(p.hand_cards);
    p.bag_cards.AddCards(p.used_cards);
    p.hand_cards.Clear();
    p.used_cards.Clear();
}

const char* get_gift_name(int i) {
    const char* gift_names[] = {
        "竭力一击",
        "生长护盾",
    };
    return gift_names[i];
}