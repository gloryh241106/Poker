#ifndef __POKER_ENGINE__
#define __POKER_ENGINE__

#include "Card_Deck.h"
#include "Comparison.h"
#include "Hand.h"
#include "Read_UserData.h"
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>

void divide_cards(std::vector<Hand> &players, int n) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < n; j++) {
            players[j].deal(1);
        }
    }
}

// Enum for representing Hand type
enum HandType{
    HIGH_CARD = 1,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};

// Evaluate hand type
int evaluateHand(Hand &hand) {
    HandType hand_rank_type;
    bool isFlush = isFlushHand(hand.cards);
    bool isStraight = isStraightHand(hand.cards);
    std::map<int, int> rankCount = getRankCounts(hand.cards);
    int highest_card_rank = 0;
    int highest_card_suit = 0;

    // Determine the hand type based on the ranking rules
    if (isStraight && isFlush) {
        hand_rank_type = STRAIGHT_FLUSH;
        
        for (auto &entry : rankCount) {
            if (entry.first > highest_card_rank) 
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (has_N_Kind(rankCount, 4)) {
        hand_rank_type = FOUR_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 4);
        for (auto &entry : rankCount) {
            if (entry.second == 4) 
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (hasFullHouse(rankCount)) {
        hand_rank_type = FULL_HOUSE;
        addRankValuesForFullHouse(rankCount);
        for (auto &entry : rankCount) {
            if (entry.second == 3) 
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (isFlush) {
        hand_rank_type = FLUSH;
        for (auto &card : hand.cards) {
            if (card.rank > highest_card_rank)
                highest_card_rank = card.rank;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (isStraight) {
        hand_rank_type = STRAIGHT;
        for (auto &entry : rankCount) {
            if (entry.first > highest_card_rank)
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (has_N_Kind(rankCount, 3)) {
        hand_rank_type = THREE_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 3);
        for (auto &entry : rankCount) {
            if (entry.second == 3) 
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (hasTwoPairs(rankCount)) {
        hand_rank_type = TWO_PAIR;
        addRankValuesForTwoPairs(rankCount);
        for (auto &entry : rankCount) {
            if (entry.second == 2 && entry.first > highest_card_rank) 
                highest_card_rank = entry.first;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else if (has_N_Kind(rankCount, 2)) {
        hand_rank_type = ONE_PAIR;
        addRankValuesForNOfAKind(rankCount, 2);
        highest_card_rank = rankValues[0];
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    } 
    else {
        hand_rank_type = HIGH_CARD;
        for (auto &card : hand.cards) {
            rankValues.push_back(card.rank);
            if (card.rank > highest_card_rank)
                highest_card_rank = card.rank;
        }
        for (auto &card : hand.cards) {
            if (card.rank == highest_card_rank) {
                highest_card_suit = card.suit;
            }
        }
    }

    // Assign highest card to hand for comparing equal hand type
    hand.highest_card_type.rank = static_cast<Rank>(highest_card_rank);
    hand.highest_card_type.suit = static_cast<Suit>(highest_card_suit);

    // Clear rankValues and rankCount after use
    reset_rankValues(rankValues);
    reset_rankCount(rankCount);

    return hand_rank_type;
}

bool compareTwoHands(Hand &hand1, Hand &hand2) {
    // First, compare hand types (higher types win)
    if (hand1.type != hand2.type) {
        return hand1.type > hand2.type;
    }

    // If hand types are the same, compare highest card ranks
    if (hand1.highest_card_type.rank != hand2.highest_card_type.rank) {
        return hand1.highest_card_type.rank > hand2.highest_card_type.rank;
    }

    // If highest cards are also the same, compare suit for further tiebreakers
    if (hand1.highest_card_type.suit > hand2.highest_card_type.suit) {
        return true;
    }

    // If all ranks are identical, the hands are equal
    return false;
}

void setRankingMatch(std::vector<Hand> &players) {
    // Evaluate each hand
    for (int i = 0; i < players.size(); i++) {
        players[i].type = evaluateHand(players[i]);
        players[i].player_index = i + 1;
    }

    std::sort(players.begin(), players.end(), compareTwoHands);
    
    for (int i = 0; i < players.size(); i++) {
        players[i].ranking_match = i + 1;
    }
}

void displayLeaderboard(std::vector<Hand> &players) {
    std::cout << "Poker Leaderboard:\n";
    int rank = 1;
    for (auto &hand : players) {
        std::cout << "Rank " << rank << ": Player " << hand.player_index 
                  << ", Hand Type " << hand.type
                  << ", Highest Card " << hand.highest_card_type.to_string()
                  << ", Ranking Match " << hand.ranking_match << "\n";
        rank++;
    }
}
#endif