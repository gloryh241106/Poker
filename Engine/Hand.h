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

    // void deal(int n) {
    //     for (int i = 0; i < n; i++) {
    //         Card temp = deck.back();
    //         cards.push_back(temp);
    //         deck.pop_back();
    //     }

    //     std::sort(cards.begin(), cards.end());
    // }
};

// d ss.    sSSSs   d     S d sss   d ss.
// S    b  S     S  S    P  S       S    b
// S    P S       S Ssss'   S       S    P
// S sS'  S       S S   s   S sSSs  S sS'
// S      S       S S    b  S       S   S
// S       S     S  S     b S       S    S
// P        "sss"   P     P P sSSss P    P

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

// Here are functions that check the type of a poker hand.
// These functions should only be called with hands' size 5

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

// Calculate the point and type of a poker hand
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
            return std::make_pair(handType, handType + hand.cards[4]);
        // Highest card of triplet, then pair
        case HandType::FULL_HOUSE:
            if (getCardRank(hand.cards[4]) == getCardRank(hand.cards[2])) {
                return std::make_pair(
                    handType, handType + hand.cards[4] * 100 + hand.cards[1]);
            }
            return std::make_pair(
                handType, handType + hand.cards[4] + hand.cards[2] * 100);
        // Highest of triplet/quad
        case HandType::FOUR_OF_A_KIND:
        case HandType::THREE_OF_A_KIND:
            return std::make_pair(handType, handType + hand.cards[2]);
        // Highest of both pair
        case HandType::TWO_PAIR: {
            int mx = std::max(hand.cards[3], hand.cards[1]);
            int mn = std::min(hand.cards[3], hand.cards[1]);
            return std::make_pair(handType, handType + mx * 100 + mn);
        }
        case HandType::ONE_PAIR:
            for (int i = 0; i < 4; i++) {
                if (getCardRank(hand.cards[i]) ==
                    getCardRank(hand.cards[i + 1])) {
                    return std::make_pair(handType, handType + hand.cards[i]);
                }
            }
            break;
        default:
            break;
    }
    return std::make_pair(handType, handType + hand.cards[4]);
}

// Ss   sS d      d ss    d s.     sSSs. d    d
//   S S   S      S   ~o  S  ~O   S      S    S
//    S    S      S     b S   `b S       S    S
//    S    S      S     S S sSSO S       S sSSS
//    S    S      S     P S    O S       S    S
//   S S   S      S    S  S    O  S      S    S
// s"   "s P      P ss"   P    P   "sss' P    P

// Here are the functions to calculate a xi dach hand value

enum XiDachHandType { QUAC, UNDERVALUE, NORMAL, XI_DACH, XI_BAN, NGU_LINH };

// Pair of aces, insta win
bool isXiBan(const Hand& hand) {
    if (hand.size != 2) return false;
    return getCardRank(hand.cards[0]) == Rank::ACE &&
           getCardRank(hand.cards[1]) == Rank::ACE;
}

// An ace with a jack/queen/king, insta win
bool isXiDach(const Hand& hand) {
    if (hand.size != 2) return false;
    int firstCardRank = getCardRank(hand.cards[0]);
    return (firstCardRank == Rank::JACK || firstCardRank == Rank::QUEEN ||
            firstCardRank == Rank::KING) &&
           getCardRank(hand.cards[1]) == Rank::ACE;
}

// Calculate the point and type of a xi dach hand
std::pair<int, int> evalXiDach(const Hand& hand) {
    if (isXiBan(hand)) return std::make_pair(XiDachHandType::XI_BAN, 1000000);
    if (isXiDach(hand)) return std::make_pair(XiDachHandType::XI_DACH, 100000);
    int total = 0;
    int aces = 0;
    for (int card : hand.cards) {
        if (card == -1) break;
        switch (getCardRank(card)) {
            case Rank::JACK:
            case Rank::QUEEN:
            case Rank::KING:
                total += 10;
                break;

            case Rank::ACE:
                aces++;
                break;

            default:
                total += getCardRank(card) + 2;
                break;
        }
    }
    // Ngu linh - Five cards that sums up to less than or equal 21 but more than
    // or equal 16
    // If two or more players reached ngu linh, the player with the lower point
    // wins, thus aces should be counted as 1 point for the lowest possible
    // point
    if (hand.size == 5 && (total + aces) <= 21) {
        return std::make_pair(XiDachHandType::NGU_LINH, total + aces);
    }

    // Aces can be either 1,10 or 11
    // If else den chet
    if (aces == 4) {
        // 11 + 1 + 1 + 1
        if (total + 14 <= 21) total += 14;
        // 10 + 1 + 1 + 1
        else if (total + 13 <= 21)
            total += 13;
        // 1 + 1 + 1 + 1
        else
            total += 4;
    } else if (aces == 3) {
        // 10 + 10 + 1
        if (total + 21 <= 21) total += 21;
        // 11 + 1 + 1
        else if (total + 13 <= 21)
            total += 13;
        // 10 + 1 + 1
        else if (total + 12 <= 21)
            total += 12;
        // 1 + 1 + 1
        else
            total += 3;
    } else if (aces == 2) {
        // 10 + 10
        if (total + 20 <= 21) total += 20;
        // 11 + 1
        else if (total + 12 <= 21)
            total += 12;
        // 10 + 1
        else if (total + 11 <= 21)
            total += 11;
        // 1 + 1
        else
            total += 2;
    } else if (aces == 1) {
        if (total + 11 <= 21)
            total += 11;
        else if (total + 10 <= 21)
            total += 10;
        else
            total += 1;
    }
    if (total < 16) return std::make_pair(XiDachHandType::UNDERVALUE, total);
    if (total > 21) return std::make_pair(XiDachHandType::QUAC, total);
    return std::make_pair(XiDachHandType::NORMAL, total);
}

#endif