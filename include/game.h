#pragma once
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "evaluator.h"
#include <vector>

class Game
{
public:
    explicit Game(long long startingCoins);

    void run();

private:
    Deck deck_;
    Hand hand_;
    Player player_;

    void dealNewHand();
    void showHand() const;
    std::vector<bool> promptHolds() const;
    long long promptBet() const;
    void addCoins();
};
