#pragma once
#include <cstdint>

class Player
{
public:
    explicit Player(int64_t bankroll = 0) : bankroll_(bankroll) {}

    int64_t bankroll() const { return bankroll_; }
    void addCoins(int64_t n)
    {
        if (n > 0)
            bankroll_ += n;
    }
    bool canBet(int64_t bet) const { return bet >= 1 && bet <= 5 && bet <= bankroll_; }
    void win(int64_t payout) { bankroll_ += payout; }
    void lose(int64_t bet) { bankroll_ -= bet; }

private:
    int64_t bankroll_{0};
};
