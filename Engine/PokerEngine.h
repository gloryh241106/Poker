#ifndef __POKER_ENGINE__
#define __POKER_ENGINE__

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include "Card.h"
#include "Hand.h"

// d ss.    sSSSs   d     S d sss   d ss.
// S    b  S     S  S    P  S       S    b
// S    P S       S Ssss'   S       S    P
// S sS'  S       S S   s   S sSSs  S sS'
// S      S       S S    b  S       S   S
// S       S     S  S     b S       S    S
// P        "sss"   P     P P sSSss P    P

// Here are functions that check the type of a poker hand.
// These functions should only be called with hands' size 5

namespace PokerEngine {

// Check if hand is a flush (five cards with same suit)
bool isFlush(const Hand& hand) {
    // If hand doesn't have 5 cards
    if (hand.size < 5) return false;
    int firstSuit = getCardSuit(hand.cards[0]);
    for (int i = 1; i < hand.size; i++) {
        if (getCardSuit(hand.cards[i]) != firstSuit) return false;
    }
    return true;
}

// Check if hand is a straight (five cards with increasing rank)
bool isStraight(const Hand& hand) {
    // If hand doesn't have 5 cards
    if (hand.size < 5) return false;
    for (int i = 1; i < hand.size; i++) {
        if (getCardRank(hand.cards[i]) != (getCardRank(hand.cards[i - 1]) + 1))
            return false;
    }
    return true;
}

// Check if the hand is of rank types. Rank types include:
// four of a kind
// full house (three of a kind + pair)
// three of a kind
// two pairs
// pair
// high card
int getHandRankType(const Hand& hand) {
    int ranks[13]{};
    int counts[5]{};

    for (int card : hand.cards) {
        if (card == -1) break;
        ranks[getCardRank(card)]++;
    }
    for (int rank : ranks) {
        counts[rank]++;
    }

    if (counts[4] == 1) return HandType::FOUR_OF_A_KIND;
    if (counts[2] >= 1 && counts[3] == 1) return HandType::FULL_HOUSE;
    if (counts[3] == 1) return HandType::THREE_OF_A_KIND;
    if (counts[2] == 2) return HandType::TWO_PAIR;
    if (counts[2] == 1) return HandType::ONE_PAIR;

    return HandType::HIGH_CARD;
}

int getHandType(const Hand& hand) {
    if (hand.size < 5) return HandType::NULL_TYPE;
    bool flush = isFlush(hand);
    bool straight = isStraight(hand);
    if (flush && straight) return HandType::STRAIGHT_FLUSH;
    if (flush) return HandType::FLUSH;
    if (straight) return HandType::STRAIGHT;

    return getHandRankType(hand);
}

// Calculate the type and point of a poker hand
std::pair<int, int> evalPoker(const Hand& hand) {
    if (hand.size < 5) return std::make_pair(HandType::NULL_TYPE, 0);
    int handType = getHandType(hand);
    // If two players has the same hand type, the player with the highest card
    // wins
    switch (handType) {
        // Highest card of hand
        case HandType::STRAIGHT_FLUSH:
        case HandType::STRAIGHT:
        case HandType::FLUSH:
        case HandType::HIGH_CARD:
            return std::make_pair(handType, hand.cards[4]);
        // Highest card of triplet, then pair
        case HandType::FULL_HOUSE:
            if (getCardRank(hand.cards[4]) == getCardRank(hand.cards[2])) {
                return std::make_pair(handType,
                                      hand.cards[4] * 100 + hand.cards[1]);
            }
            return std::make_pair(handType,
                                  hand.cards[4] + hand.cards[2] * 100);
        // Highest of triplet/quad
        case HandType::FOUR_OF_A_KIND:
        case HandType::THREE_OF_A_KIND:
            return std::make_pair(handType, hand.cards[2]);
        // Highest of both pair
        case HandType::TWO_PAIR: {
            int mx = std::max(hand.cards[3], hand.cards[1]);
            int mn = std::min(hand.cards[3], hand.cards[1]);
            return std::make_pair(handType, mx * 100 + mn);
        }
        case HandType::ONE_PAIR:
            for (int i = 0; i < 4; i++) {
                if (getCardRank(hand.cards[i]) ==
                    getCardRank(hand.cards[i + 1])) {
                    return std::make_pair(handType, hand.cards[i]);
                }
            }
            break;
        default:
            break;
    }
    return std::make_pair(handType, hand.cards[4]);
}

}  // namespace PokerEngine

#endif