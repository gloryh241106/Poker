#ifndef __XIDACH_ENGINE__
#define __XIDACH_ENGINE__

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include "Card.h"
#include "Hand.h"

// Ss   sS d      d ss    d s.     sSSs. d    d
//   S S   S      S   ~o  S  ~O   S      S    S
//    S    S      S     b S   `b S       S    S
//    S    S      S     S S sSSO S       S sSSS
//    S    S      S     P S    O S       S    S
//   S S   S      S    S  S    O  S      S    S
// s"   "s P      P ss"   P    P   "sss' P    P

// Here are the functions to calculate a xi dach hand value

enum XiDachHandType { QUAC = 0, UNDERVALUE, NORMAL, XI_DACH, XI_BAN, NGU_LINH };

namespace XiDachEngine {
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

std::string type(std::pair<int, int> eval) {
    if (eval.first == XiDachHandType::XI_BAN) return "(Xi Ban)";
    if (eval.first == XiDachHandType::XI_DACH) return "(Xi Dach)";
    if (eval.first == XiDachHandType::QUAC) return "(Quac)";
    if (eval.first == XiDachHandType::NGU_LINH) return "(Ngu linh)";
    return "";
}
}  // namespace XiDachEngine

#endif