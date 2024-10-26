#include <iostream>
#include <vector>
#include "Engine/Engine.h"

int main() {
    // Printing greetings
    std::cout << "Welcome to Poker!" << std::endl;

    // Initialize a deck
    Deck deck;

    // Shuffle
    deck.shuffle();

    // Create a player
    Player player1;

    // Draw 5 card
    player1.getCard();

    // Print the cards
    player1.displayHand();

    // Get the rank of 5 cards 
    /*  HIGH_CARD = 1,
        ONE_PAIR = 2,
        TWO_PAIR = 3,
        THREE_OF_A_KIND = 4,
        STRAIGHT = 5,
        FLUSH = 6,
        FULL_HOUSE = 7,
        FOUR_OF_A_KIND = 8,
        STRAIGHT_FLUSH = 9
    */
    player1.evaluateRank();

    std::cout << player1.ranking_match << std::endl;

    return 0;
}