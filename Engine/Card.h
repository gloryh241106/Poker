#ifndef __CARD__
#define __CARD__

// Cards in the game
// Each card is an int: RANK * 4 + SUIT

#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <vector>

// Enum for Suit
enum Suit { SPADES = 0, CLUBS, DIAMONDS, HEARTS };

// Enum for Rank
enum Rank {
    TWO = 0,
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

std::string suitStringLookup[] = {"s", "c", "d", "h"};
std::string rankStringLookup[] = {"2", "3",  "4", "5", "6", "7", "8",
                                  "9", "10", "j", "q", "k", "a"};

int getCardRank(int card) { return card == -1 ? -1 : card / 4; }

int getCardSuit(int card) { return card == -1 ? -1 : card % 4; }

// Get a human readable card
std::string cardToString(int card) {
    int rank = getCardRank(card);
    int suit = getCardSuit(card);
    return rankStringLookup[rank] + suitStringLookup[suit];
}

std::vector<int> generateDeck(unsigned int seed = 0) {
    // Generate a 52 cards deck
    std::vector<int> deck(52, 0);
    for (int i = 0; i < 52; i++) {
        deck[i] = i;
    }
    // Shuffle the deck
    std::mt19937 rng(seed == 0 ? static_cast<unsigned int>(std::time(0))
                               : seed);
    std::shuffle(deck.begin(), deck.end(), rng);
    return deck;
}

#endif