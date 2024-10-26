#include <iostream>
#include <vector>
#include "Engine/Engine.h"

int main() {
    std::cout << "Welcome to Poker!" << std::endl;

    Deck deck;
    deck.shuffle();

    Player player1;
    player1.getCard();
    player1.displayHand();
    player1.evaluateRank();

    std::cout << player1.ranking_match << std::endl;

    return 0;
}