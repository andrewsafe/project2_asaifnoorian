#pragma once
#include "card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck
{
public:
    Deck();
    void shuffle();
    Card deal();

private:
    std::vector<Card> cards_;
    size_t idx_{0};
    std::mt19937_64 rng_;
    void reset();
};
