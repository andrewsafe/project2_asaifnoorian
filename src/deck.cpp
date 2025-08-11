#include "deck.h"
#include <chrono>

Deck::Deck()
{
    rng_.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    reset();
}

void Deck::reset()
{
    cards_.clear();
    for (int s = 0; s < 4; ++s)
        for (int r = 2; r <= 14; ++r)
            cards_.emplace_back(r, static_cast<Suit>(s));
    idx_ = 0;
}

void Deck::shuffle()
{
    reset();
    std::shuffle(cards_.begin(), cards_.end(), rng_);
}

Card Deck::deal()
{
    if (idx_ >= cards_.size())
        shuffle();
    return cards_[idx_++];
}
