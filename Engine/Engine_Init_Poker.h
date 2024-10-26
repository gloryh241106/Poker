#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

#include <random>
#include <algorithm>
#include "Engine_Poker_Comparison.h"
#include "Engine_Card_Deck.h"

// Enum to represent hand rankings

enum HandRank{
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

// Create 2 boolean variables for checking Flush, Straight, or Straight Flush

bool isFlush = false;
bool isStraight = false;

//Player hand
class Player {
    public:
        std::vector<Card> player_hands;
        int ranking_match;
        std::vector<int> rankValues;

        void getCard() {
            for (int i = 0; i < 5; i++) {
                player_hands.push_back(deck.dealCard());
            }
        }

        void displayHand() {
            std::cout << "Your hand: " << std::endl;
            for (auto card : player_hands) {
                card.print();
            }
        }

        // Evaluating
        void evaluateRank(){
            bool isFlush = isFlushHand(player_hands);
            bool isStraight = isStraightHand(player_hands);
            std::map<int, int> rankCount = getRankCounts(player_hands);

            if (isStraight && isFlush) {
                ranking_match = STRAIGHT_FLUSH;
                rankValues.push_back(player_hands.back().rank); // Highest card in straight
            } 
            else if (has_N_Kind(rankCount, 4)) {
                ranking_match = FOUR_OF_A_KIND;
                addRankValuesForNOfAKind(rankCount, 4);
            } 
            else if (hasFullHouse(rankCount)) {
                ranking_match = FULL_HOUSE;
                addRankValuesForFullHouse(rankCount);
            } 
            else if (isFlush) {
                ranking_match = FLUSH;
                for (int i = 0; i < player_hands.size(); ++i)
                    rankValues.push_back(player_hands[i].rank); // Highest cards in flush
            } 
            else if (isStraight) {
                ranking_match = STRAIGHT;
                rankValues.push_back(player_hands.back().rank); // Highest card in straight
            } 
            else if (has_N_Kind(rankCount, 3)) {
                ranking_match = THREE_OF_A_KIND;
                addRankValuesForNOfAKind(rankCount, 3);
            } 
            else if (hasTwoPairs(rankCount)) {
                ranking_match = TWO_PAIR;
                addRankValuesForTwoPairs(rankCount);
            } 
            else if (has_N_Kind(rankCount, 2)) {
                ranking_match = ONE_PAIR;
                addRankValuesForNOfAKind(rankCount, 2);
            } 
            else {
                ranking_match = HIGH_CARD;
                for (int i = 0; i < player_hands.size(); ++i)
                    rankValues.push_back(player_hands[i].rank); // Highest cards
            }
        }
    private:
        Deck deck;
};

#endif