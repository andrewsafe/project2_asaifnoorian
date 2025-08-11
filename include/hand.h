#pragma once
#include "card.h"
#include <array>
#include <vector>

class Hand
{
public:
    Hand() = default;

    void clear();
    void add(const Card &c);
    const std::array<Card, 5> &cards() const { return cards_; }
    std::array<Card, 5> &cards() { return cards_; }

    void replaceExceptHolds(const std::vector<bool> &holdMask, class Deck &deck);

private:
    std::array<Card, 5> cards_{};
    int filled_{0};
};
