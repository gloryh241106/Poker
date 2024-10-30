#include <iostream>
#include <vector>
#include "Engine/PokerEngine.h"

int main() {
    std::cout << "Welcome to Poker!" << std::endl;
    initDeck(deck);
    Hand player1;
    Hand player2;

    player1.deal(5);
    player2.deal(5);

    player1.toString();
    std::cout << std::endl;
    player2.toString();
    std::cout << std::endl;

    player1.type = evaluateHand(player1);
    player2.type = evaluateHand(player2);
    std::cout << player1.type << std::endl;
    std::cout << player2.type << std::endl;

    return 0;
}