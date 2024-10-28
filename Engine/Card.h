#ifndef __CARD__
#define __CARD__

//Cards in the game

#include <algorithm>
#include <vector>
#include <string>

// Enum for Suit
enum Suit {
    SPADES,
    CLUBS,
    DIAMOND,
    HEARTS
};

//Enum for Rank
enum Rank {
    TWO = 2, 
    THREE, 
    FOUR, 
    FIVE, 
    SIX, 
    SEVEN, 
    EIGHT, 
    NINE, 
    TEN, 
    JACK, 
    QUEEN, 
    KING, 
    ACE
};

// Create a struct for each card
struct Card {
    Rank rank;
    Suit suit;

    std::string to_string() {
        std::string suit_str[] = {"s", "c", "d", "h"};
        return std::to_string(rank) + suit_str[suit];
    }
};

#endif