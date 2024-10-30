#ifndef __CARD__
#define __CARD__

//Cards in the game

#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>

// Enum for Suit
enum Suit {
    SPADES,
    CLUBS,
    DIAMOND,
    HEARTS
};

// Enum for Rank
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

std::vector<Card> deck;

void initDeck(std::vector<Card> &deck) {
    for (int r = TWO; r <= ACE; r++) {
        for (int s = SPADES; s <= HEARTS; s++) {
            Card card = {static_cast<Rank>(r), static_cast<Suit>(s)};
            deck.emplace_back(card);
        }
    }
    std::mt19937 rng(static_cast<unsigned int>(std::time(0)));
    std::shuffle (deck.begin(), deck.end(), rng);
    std::shuffle (deck.begin(), deck.end(), rng);
}

#endif