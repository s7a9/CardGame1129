#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Cards.h"

bool cmp_cards(const card_t& c1, const card_t& c2) {
    return c1.type == c2.type && c1.value == c2.value && c1.ap_cost == c2.ap_cost;
}

void CardList::Add(card_t item) {
    cards.push_back(item);
}

void CardList::AddCards(card_t items[], int n) {
    for (int i = 0; i < n; i++) {
        cards.push_back(items[i]);
    }
}

void CardList::Remove(int index) {
    if (index < 0 || index >= Size()) {
        return;
    }
    cards.erase(cards.begin() + index);
}

void CardList::Remove(card_t card) {
    for (auto iter = cards.begin(); iter != cards.end(); ++iter) {
        if (cmp_cards(*iter, card)) {
            cards.erase(iter);
            break;
        }
    }
}

card_t& CardList::Get(int index) {
    return cards.at(index);
}

card_t& CardList::operator[](int index) {
    return cards[index];
}

int CardList::Size() const {
    return cards.size();
}

void CardList::Shuffle() {
    int n = Size(), l;
    for (int i = n - 1; i >= 0; --i) {
        l = rand() % (i + 1);
        if (l != i) std::swap(cards[l], cards[i]);
    }
}

void CardList::Clear() {
    cards.clear();
}

using namespace std;