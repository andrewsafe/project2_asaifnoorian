#include "hand.h"
#include "deck.h"

void Hand::clear() { filled_ = 0; }

void Hand::add(const Card &c)
{
    if (filled_ < 5)
        cards_[filled_++] = c;
}

void Hand::replaceExceptHolds(const std::vector<bool> &holdMask, Deck &deck)
{
    for (int i = 0; i < 5; ++i)
    {
        if (i >= (int)holdMask.size() || !holdMask[i])
        {
            cards_[i] = deck.deal();
        }
    }
}
