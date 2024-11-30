#ifndef __CARD__
#define __CARD__

// Cards in the game
// Each card is an int: RANK * 4 + SUIT

#include <algorithm>
#include <deque>
#include <string>

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

std::string suitStringLookup[] = {"♠", "♣", "♦", "♥"};
std::string rankStringLookup[] = {"2", "3",  "4", "5", "6", "7", "8",
                                  "9", "10", "j", "q", "k", "a"};

int getCardRank(int card) {
    return card == -1 ? -1 : card >> 2;  // card / 4
}

int getCardSuit(int card) {
    return card == -1 ? -1 : card & 3;  // card % 4
}

// Get a human readable card
std::string cardToString(int card) {
    if (card == -1) return "..";
    int rank = getCardRank(card);
    int suit = getCardSuit(card);
    return rankStringLookup[rank] + suitStringLookup[suit];
}

class Deck {
   private:
    int deck[52];
    int deckTop = 51;
    uint64_t deckBit = 0x000fffffffffffff;
    //                      AKQJT98765432

   public:
    Deck() {
        for (int i = 0; i < 52; i++) {
            deck[i] = i;
        }
        // Shuffle the deck
        std::shuffle(deck, deck + 52, Random::globalRNG);
    }

    // Deal a card from the top of the deck
    int top() {
        if (deckTop < 0) return -1;
        return deck[deckTop];
    }

    void pop() {
        if (deckTop < 0) return;
        deckBit &= ~(1ll << deck[deckTop]);
        deckTop--;
    }

    int draw() {
        int topCard = top();
        pop();
        return topCard;
    }

    void push(int card) {
        if (deckBit & (1ll << card)) return;
        deckBit |= (1ll << card);
        deck[++deckTop] = card;
    }

    uint64_t bit() { return deckBit; }

    // Generate a new deck
    void newDeck() {
        // Shuffle the deck
        std::shuffle(deck, deck + 52, Random::globalRNG);
        deckTop = 51;
    }
};

#endif