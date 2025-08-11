#pragma once
#include <string>
#include <array>

enum class Suit
{
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3
};

struct Card
{
    int rank;
    Suit suit;

    Card(int r = 2, Suit s = Suit::Clubs) : rank(r), suit(s) {}

    std::string rankStr() const
    {
        static const std::array<std::string, 15> R = {
            "", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        return R[rank];
    }
    std::string suitStr() const
    {
        switch (suit)
        {
        case Suit::Clubs:
            return "C";
        case Suit::Diamonds:
            return "D";
        case Suit::Hearts:
            return "H";
        case Suit::Spades:
            return "S";
        }
        return "?";
    }
    std::string toString() const { return rankStr() + suitStr(); }
};
