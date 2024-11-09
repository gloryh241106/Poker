#ifndef __CARD__
#define __CARD__

// Cards in the game
// Each card is an int: RANK * 4 + SUIT

#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <vector>

#include "Random.h"

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

// std::vector<int> generateDeck(unsigned int seed = 0) {
//     // Generate a 52 cards deck
//     std::vector<int> deck(52, 0);
//     for (int i = 0; i < 52; i++) {
//         deck[i] = i;
//     }
//     // Shuffle the deck
//     std::shuffle(deck.begin(), deck.end(), globalRNG);
//     return deck;
// }

class Deck {
   private:
    int deck[52];
    int deckTop = 51;

   public:
    Deck() {
        for (int i = 0; i < 52; i++) {
            deck[i] = i;
        }
        // Shuffle the deck
        std::shuffle(deck, deck + 52, globalRNG);
    }

    // Deal a card from the top of the deck
    int top() {
        if (deckTop < 0) return -1;
        return deck[deckTop];
    }

    void pop() { deckTop--; }

    // Generate a new deck
    void newDeck() {
        // Shuffle the deck
        std::shuffle(deck, deck + 52, globalRNG);
        deckTop = 51;
    }
};

#endif