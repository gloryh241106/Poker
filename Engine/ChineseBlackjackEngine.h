#ifndef __ChineseBlackjack_ENGINE__
#define __ChineseBlackjack_ENGINE__

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include "Card.h"
#include "Hand.h"

/*
   ____ _     _                       ____       _             
  / ___| |__ (_)_ __   ___ ___  ___  |  _ \ ___ | | _____ _ __ 
 | |   | '_ \| | '_ \ / _ / __|/ _ \ | |_) / _ \| |/ / _ | '__|
 | |___| | | | | | | |  __\__ |  __/ |  __| (_) |   |  __| |   
  \____|_| |_|_|_| |_|\___|___/\___| |_|   \___/|_|\_\___|_|   
                                                                                                                                                                                  
*/
// Here are the functions to calculate a xi dach hand value

enum ChineseBlackjackHandType { QUAC = 0, UNDERVALUE, NORMAL, XI_DACH, XI_BAN, NGU_LINH };

namespace ChineseBlackjackEngine {
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
        int secondCardRank = getCardRank(hand.cards[1]);
        return ((firstCardRank == Rank::JACK || firstCardRank == Rank::QUEEN ||
                firstCardRank == Rank::KING) &&
            secondCardRank == Rank::ACE) || 
            ((secondCardRank == Rank::JACK || secondCardRank == Rank::QUEEN ||
                secondCardRank == Rank::KING) &&
            firstCardRank == Rank::ACE);
    }

    // Calculate the point and type of a xi dach hand
    std::pair<int, int> evalChineseBlackjack(const Hand& hand) {
        if (isXiBan(hand)) return std::make_pair(ChineseBlackjackHandType::XI_BAN, 1000000);
        if (isXiDach(hand)) return std::make_pair(ChineseBlackjackHandType::XI_DACH, 100000);
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
            return std::make_pair(ChineseBlackjackHandType::NGU_LINH, total + aces);
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

        if (total < 16) return std::make_pair(ChineseBlackjackHandType::UNDERVALUE, total);
        if (total > 21) return std::make_pair(ChineseBlackjackHandType::QUAC, total);

        return std::make_pair(ChineseBlackjackHandType::NORMAL, total);
    }

    std::string type(std::pair<int, int> eval) {
        if (eval.first == ChineseBlackjackHandType::XI_BAN) return "(Xi Ban)";
        if (eval.first == ChineseBlackjackHandType::XI_DACH) return "(Xi Dach)";
        if (eval.first == ChineseBlackjackHandType::QUAC) return "(Quac)";
        if (eval.first == ChineseBlackjackHandType::NGU_LINH) return "(Ngu linh)";
        
        return "";
    }
}  // namespace ChineseBlackjackEngine

#endif