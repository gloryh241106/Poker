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

// Enum for hand types

enum HandType : uint64_t {
    HIGH_CARD = 1ull << 52,
    ONE_PAIR = 1ull << 53,
    TWO_PAIR = 1ull << 54,
    THREE_OF_A_KIND = 1ull << 55,
    LOW_ACE_STRAIGHT = 1ull << 56,
    STRAIGHT = 1ull << 57,
    FLUSH = 1ull << 58,
    FULL_HOUSE = 1ull << 59,
    FOUR_OF_A_KIND = 1ull << 60,
    LOW_ACE_STRAIGHT_FLUSH = 1ull << 61,
    STRAIGHT_FLUSH = 1ull << 62,
    NULL_TYPE = 0
};

const uint64_t TYPE_MASK = 0xfff0000000000000;
const uint64_t HAND_MASK = 0x000fffffffffffff;

const uint64_t QUAD_MASK = 0xf;
const uint64_t STRAIGHT_MASK = 0xfffff;
const uint64_t ACE_STRAIGHT_MASK = 0x000f00000000ffff;
const uint64_t FLUSH_MASK = 0x0001111111111111;

// Calculate the type and point of a poker hand
void eval(uint64_t& handBit) {
    // Clear the type
    handBit &= HAND_MASK;
    // Flush check
    bool isFlush = false;
    for (int i = 0; i < 4; i++) {
        if (__builtin_popcountll(handBit & (FLUSH_MASK << i)) == 5) {
            isFlush = true;
            break;
        }
    }
    // Straight check
    bool isStraight = false;
    bool lowAce = false;
    if (__builtin_popcountll(handBit & ACE_STRAIGHT_MASK) == 5) {
        isStraight = true;
        lowAce = true;
        for (int j = 0; j < 4; j++) {
            if (__builtin_popcountll(handBit & (QUAD_MASK << (j << 2))) != 1) {
                isStraight = false;
                lowAce = false;
                break;
            }
        }
        if (__builtin_popcountll(handBit & (QUAD_MASK << (13 << 2))) != 1) {
            isStraight = false;
            lowAce = false;
        }
    } else {
        for (int i = 0; i < 9; i++) {
            if (__builtin_popcountll(handBit & (STRAIGHT_MASK << (i << 2))) ==
                5) {
                isStraight = true;
                for (int j = 0; j < 5; j++) {
                    if (__builtin_popcountll(
                            handBit & (QUAD_MASK << (i << 2) << (j << 2))) !=
                        1) {
                        isStraight = false;
                        break;
                    }
                }
                break;
            }
        }
    }
    bool isStraightFlush = isStraight && isFlush;

    if (isStraightFlush) {
        if (lowAce)
            handBit |= HandType::LOW_ACE_STRAIGHT_FLUSH;
        else
            handBit |= HandType::STRAIGHT_FLUSH;
        return;
    }

    bool isFourOfAKind = false;
    for (int i = 0; i < 52; i += 4) {
        if (__builtin_popcountll(handBit & (QUAD_MASK << i)) == 4) {
            isFourOfAKind = true;
            break;
        }
    }

    if (isFourOfAKind) {
        handBit |= HandType::FOUR_OF_A_KIND;
        return;
    }

    int pairCount = 0;
    int tripleCount = 0;
    for (int i = 0; i < 13; i++) {
        if (__builtin_popcountll(handBit & (QUAD_MASK << (i << 2))) == 2) {
            pairCount++;
        } else if (__builtin_popcountll(handBit & (QUAD_MASK << (i << 2))) ==
                   3) {
            tripleCount++;
        }
    }

    if (tripleCount == 1 && pairCount == 1) {
        handBit |= HandType::FULL_HOUSE;
        return;
    }

    if (isStraight) {
        if (lowAce)
            handBit |= HandType::LOW_ACE_STRAIGHT;
        else
            handBit |= HandType::STRAIGHT;
        return;
    }
    if (isFlush) {
        handBit |= HandType::FLUSH;
        return;
    }

    if (tripleCount == 1) {
        handBit |= HandType::THREE_OF_A_KIND;
        return;
    }

    if (pairCount == 2) {
        handBit |= HandType::TWO_PAIR;
        return;
    }

    if (pairCount == 1) {
        handBit |= HandType::ONE_PAIR;
        return;
    }

    handBit |= HandType::HIGH_CARD;
}

std::string type(const Hand& hand) {
    uint64_t type = hand.bit() & TYPE_MASK;
    switch (type) {
        case HandType::HIGH_CARD:
            return "High card";
        case HandType::ONE_PAIR:
            return "One pair";
        case HandType::TWO_PAIR:
            return "Two pair";
        case HandType::THREE_OF_A_KIND:
            return "Three of a kind";
        case HandType::LOW_ACE_STRAIGHT:
            return "Low ace straight";
        case HandType::STRAIGHT:
            return "Straight";
        case HandType::FLUSH:
            return "Flush";
        case HandType::FULL_HOUSE:
            return "Full house";
        case HandType::FOUR_OF_A_KIND:
            return "Four of a kind";
        case HandType::LOW_ACE_STRAIGHT_FLUSH:
            return "Low ace straight flush";
        case HandType::STRAIGHT_FLUSH:
            return "Straight flush";
        default:
            break;
    }
    return "Unknown";
}

bool compareHands(const Hand& hand1, const Hand& hand2) {
    uint64_t type1 = hand1.bit() & TYPE_MASK;
    uint64_t type2 = hand2.bit() & TYPE_MASK;

    if (type1 != type2) return type1 > type2;

    return hand1.compressedBit() > hand2.compressedBit();
}

}  // namespace PokerEngine

#endif