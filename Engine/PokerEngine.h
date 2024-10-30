#ifndef __POKER_ENGINE__
#define __POKER_ENGINE__

#include "Card_Deck.h"
#include "Comparison.h"
#include "Hand.h"
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>

std::string name;

// Evaluating

int evaluateHand(Hand &hand){
    int hand_rank_type;
    bool isFlush = isFlushHand(hand.cards);
    bool isStraight = isStraightHand(hand.cards);
    std::map<int, int> rankCount = getRankCounts(hand.cards);

    if (isStraight && isFlush) {
        hand_rank_type = STRAIGHT_FLUSH;
         // Highest card in straight
    } 
    else if (has_N_Kind(rankCount, 4)) {
        hand_rank_type = FOUR_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 4);
    } 
    else if (hasFullHouse(rankCount)) {
        hand_rank_type = FULL_HOUSE;
        addRankValuesForFullHouse(rankCount);
    } 
    else if (isFlush) {
        hand_rank_type = FLUSH;
        for (int i = 0; i < hand.cards.size(); i++)
            // Highest cards in flush
            
            rankValues.push_back(hand.cards[i].rank); 
        } 
    else if (isStraight) {
        hand_rank_type = STRAIGHT;
        // Highest card in straight
        rankValues.push_back(hand.cards.back().rank); 
    } 
    else if (has_N_Kind(rankCount, 3)) {
        hand_rank_type = THREE_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 3);
    } 
    else if (hasTwoPairs(rankCount)) {
        hand_rank_type = TWO_PAIR;
        addRankValuesForTwoPairs(rankCount);
    } 
    else if (has_N_Kind(rankCount, 2)) {
        hand_rank_type = ONE_PAIR;
        addRankValuesForNOfAKind(rankCount, 2);
    } 
    else {
        hand_rank_type = HIGH_CARD;
        for (int i = 0; i < hand.cards.size(); ++i)
            // Highest cards
            rankValues.push_back(hand.cards[i].rank); 
    }
    return hand_rank_type;
}

#endif