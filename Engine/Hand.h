#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

// Hand
#include <algorithm>
#include <random>

#include "Card.h"

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    NULL_TYPE
};

struct Hand {
    int cards[5] = {-1, -1, -1, -1, -1};
    int size = 0;
    int type = HandType::NULL_TYPE;

    bool add(int card) {
        if (size >= 5) return false;
        cards[size] = card;
        size++;
        std::sort(cards, cards + size);

        return true;
    }

    std::string toString() {
        std::string handString;

        for (int i = 0; i < size; i++) {
            handString += cardToString(cards[i]);
            if (!(i == size - 1)) handString += ' ';
        }

        return handString;
    }
};

// Counting how many times each rank appers in hands
int getRankCount(int rank, const Hand& hand) {
    // Zero card in hand
    if (hand.size <= 0) return 0;
    int count = 0;
    for (int card : hand.cards) {
        if (card == -1) break;
        if (getCardRank(card) == rank) count++;
    }
    return count;
}

#endif