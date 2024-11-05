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
    divideCards(players, n);
    displayHands(players, n);
    setRankingMatch(players);
    displayLeaderboard(players);
    
    return 0;
}