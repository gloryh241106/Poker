#include <iostream>
#include <vector>
#include "Engine/PokerEngine.h"

int main() {
    std::cout << "Welcome to Poker!" << std::endl;

    initDeck(deck);

    int n;
    std::cout << "How much player do you want: ";
    std::cin >> n;

    std::vector<Hand> players(n);
    divide_cards(players, n);
    for (int i = 0; i < n; i++) {
        std::cout << "Player " << i + 1 << " : ";
        for (auto card : players[i].cards) {
            std::cout << card.to_string() << " ";
        }
        std::cout << std::endl;
    }

    setRankingMatch(players);
    displayLeaderboard(players);
    
    return 0;
}