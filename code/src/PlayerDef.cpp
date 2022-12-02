#include "PlayerDef.h"
#include <cstdlib>

using namespace std;

void draw_a_card(player_t* p) {
    if (p->bag_cards.Size()) {
        p->hand_cards.Add(p->bag_cards[0]);
        p->bag_cards.Remove(0);
    }
    else {
        while (p->used_cards.Size()) {
            p->bag_cards.Add(p->used_cards[0]);
            p->used_cards.Remove(0);
        }
        p->bag_cards.Shuffle();
    }
}

void prepare_turn(player_t* p) {
    int draw_cards_n = 2 + p->level / 2;
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
    while (p.hand_cards.Size()) {
        p.bag_cards.Add(p.hand_cards[0]);
        p.hand_cards.Remove(0);
    }
    while (p.used_cards.Size()) {
        p.bag_cards.Add(p.used_cards[0]);
        p.used_cards.Remove(0);
    }
}