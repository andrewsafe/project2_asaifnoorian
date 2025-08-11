#include "game.h"
#include <iostream>
#include <sstream>
#include <limits>

Game::Game(long long startingCoins) : player_(startingCoins) {}

void Game::dealNewHand()
{
    hand_.clear();
    deck_.shuffle();
    for (int i = 0; i < 5; ++i)
        hand_.add(deck_.deal());
}

void Game::showHand() const
{
    std::cout << "Your hand: ";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "[" << (i + 1) << ":" << hand_.cards()[i].toString() << "] ";
    }
    std::cout << "\n";
}

std::vector<bool> Game::promptHolds() const
{
    std::vector<bool> hold(5, false);
    std::cout << "Enter positions to HOLD (e.g., 1 3 5). Press Enter for none: ";
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int x;
    while (iss >> x)
        if (x >= 1 && x <= 5)
            hold[x - 1] = true;
    return hold;
}

long long Game::promptBet() const
{
    while (true)
    {
        std::cout << "Place your bet (1-5, ≤ bankroll " << player_.bankroll() << "): ";
        long long b;
        if (!(std::cin >> b))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (player_.canBet(b))
            return b;
        std::cout << "Invalid bet.\n";
    }
}

void Game::addCoins()
{
    std::cout << "Add coins (0 to skip): ";
    long long n;
    if (!(std::cin >> n))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        n = 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    player_.addCoins(n);
}

void Game::run()
{
    std::cout << "=== Video Poker (console) ===\n";
    while (true)
    {
        std::cout << "\nBankroll: " << player_.bankroll() << " coins\n";
        std::cout << "[N]ew hand  [A]dd coins  [Q]uit: ";
        char cmd;
        std::cin >> cmd;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (cmd == 'q' || cmd == 'Q')
        {
            std::cout << "Cash out: " << player_.bankroll() << " coins\n";
            break;
        }
        if (cmd == 'a' || cmd == 'A')
        {
            addCoins();
            continue;
        }
        if (cmd != 'n' && cmd != 'N')
            continue;

        if (player_.bankroll() <= 0)
        {
            std::cout << "You’re broke. Add coins.\n";
            continue;
        }

        long long bet = promptBet();
        dealNewHand();
        showHand();
        auto hold = promptHolds();
        hand_.replaceExceptHolds(hold, deck_);
        showHand();

        auto res = HandEvaluator::evaluate(hand_);
        if (res.multiplier > 0)
        {
            long long won = res.multiplier * bet;
            player_.win(won);
            std::cout << "Result: " << res.name << "  Payout +" << won << "\n";
        }
        else
        {
            player_.lose(bet);
            std::cout << "Result: " << res.name << "  Lose -" << bet << "\n";
        }
    }
}
