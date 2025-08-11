#include "evaluator.h"
#include <algorithm>
#include <vector>

static EvalResult make(HandRank r, int mult, const char *name)
{
    return EvalResult{r, mult, name};
}

void HandEvaluator::rankCounts(const Hand &h, int counts[15])
{
    std::fill(counts, counts + 15, 0);
    for (auto &c : h.cards())
        counts[c.rank]++;
}

bool HandEvaluator::isFlush(const Hand &h)
{
    auto s = h.cards()[0].suit;
    for (int i = 1; i < 5; ++i)
        if (h.cards()[i].suit != s)
            return false;
    return true;
}

bool HandEvaluator::isStraight(const Hand &h, int &high)
{
    std::vector<int> r;
    r.reserve(5);
    for (auto &c : h.cards())
        r.push_back(c.rank);
    std::sort(r.begin(), r.end());
    if (r == std::vector<int>({2, 3, 4, 5, 14}))
    {
        high = 5;
        return true;
    }
    for (int i = 1; i < 5; ++i)
        if (r[i] != r[0] + i)
            return false;
    high = r.back();
    return true;
}

EvalResult HandEvaluator::evaluate(const Hand &h)
{
    const bool flush = isFlush(h);
    int highStraight = 0;
    const bool straight = isStraight(h, highStraight);

    int cnt[15];
    rankCounts(h, cnt);

    int pairs = 0, threes = 0, fours = 0;
    int pairRankMax = 0;
    for (int r = 2; r <= 14; ++r)
    {
        if (cnt[r] == 4)
            fours++;
        else if (cnt[r] == 3)
            threes++;
        else if (cnt[r] == 2)
        {
            pairs++;
            pairRankMax = std::max(pairRankMax, r);
        }
    }

    if (straight && flush)
    {
        std::vector<int> r;
        for (auto &c : h.cards())
            r.push_back(c.rank);
        std::sort(r.begin(), r.end());
        if (r == std::vector<int>({10, 11, 12, 13, 14}))
            return make(HandRank::RoyalFlush, 250, "Royal Flush");
        return make(HandRank::StraightFlush, 50, "Straight Flush");
    }
    if (fours == 1)
        return make(HandRank::FourOfAKind, 25, "Four of a Kind");
    if (threes == 1 && pairs == 1)
        return make(HandRank::FullHouse, 9, "Full House");
    if (flush)
        return make(HandRank::Flush, 6, "Flush");
    if (straight)
        return make(HandRank::Straight, 4, "Straight");
    if (threes == 1)
        return make(HandRank::ThreeOfAKind, 3, "Three of a Kind");
    if (pairs == 2)
        return make(HandRank::TwoPair, 2, "Two Pair");
    if (pairs == 1 && (pairRankMax >= 11 || pairRankMax == 14))
        return make(HandRank::JacksOrBetter, 1, "Jacks or Better");
    return make(HandRank::NoHand, 0, "No Hand");
}
