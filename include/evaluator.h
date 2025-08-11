#pragma once
#include "card.h"
#include "hand.h"
#include <string>
#include <utility>

enum class HandRank
{
    NoHand = 0,
    JacksOrBetter,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

struct EvalResult
{
    HandRank rank;
    int multiplier;
    std::string name;
};

class HandEvaluator
{
public:
    static EvalResult evaluate(const Hand &h);

private:
    static bool isFlush(const Hand &h);
    static bool isStraight(const Hand &h, int &high);
    static void rankCounts(const Hand &h, int counts[15]);
};
