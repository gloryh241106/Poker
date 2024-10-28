#ifndef __POKER_ENGINE__
#define __POKER_ENGINE__

#include "Card.h"
#include "Comparison.h"
#include "Hand.h"
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>

std::string name;

// Create a deck
class Deck {
public:
    std::vector<Card> deal(int n) {
        // Storing dealt card
        std::vector<Card> dealtCard;

        for (int i = 0; i < n; i++) {
            Card tempCard = deck.back();

            dealtCard.push_back(tempCard);
            deck.pop_back();        
        }

        return dealtCard;
    }

    void init() {
        for (int s = SPADES; s <= HEARTS; ++s) {
            for (int r = TWO; r <= ACE; ++r) {
                Card card = {static_cast<Rank>(r), static_cast<Suit>(s)};
                deck.push_back(card);
            }
        }
        shuffle();
    }

    // Shuffle the deck
    void shuffle() {
        // Seed the random number generator
        std::mt19937 rng(static_cast<unsigned int>(std::time(0)));

        // Shuffle the deck - Shuffle 3 times for better randomize =))
        std::shuffle(deck.begin(), deck.end(), rng);
        std::shuffle(deck.begin(), deck.end(), rng);
        std::shuffle(deck.begin(), deck.end(), rng);
    }
private:
    std::vector<Card> deck;
};

// Evaluating

int evaluateHand(Hand hand){
    bool isFlush = isFlushHand(hand.cards);
    bool isStraight = isStraightHand(hand.cards);
    std::map<int, int> rankCount = getRankCounts(hand.cards);

    if (isStraight && isFlush) {
        hand.type = STRAIGHT_FLUSH;
         // Highest card in straight
    } 
    else if (has_N_Kind(rankCount, 4)) {
        hand.type = FOUR_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 4);
    } 
    else if (hasFullHouse(rankCount)) {
        hand.type = FULL_HOUSE;
        addRankValuesForFullHouse(rankCount);
    } 
    else if (isFlush) {
        hand.type = FLUSH;
        for (int i = 0; i < hand.cards.size(); i++)
            // Highest cards in flush
            
            rankValues.push_back(hand.cards[i].rank); 
        } 
    else if (isStraight) {
        hand.type = STRAIGHT;
        // Highest card in straight
        rankValues.push_back(hand.cards.back().rank); 
    } 
    else if (has_N_Kind(rankCount, 3)) {
        hand.type = THREE_OF_A_KIND;
        addRankValuesForNOfAKind(rankCount, 3);
    } 
    else if (hasTwoPairs(rankCount)) {
        hand.type = TWO_PAIR;
        addRankValuesForTwoPairs(rankCount);
    } 
    else if (has_N_Kind(rankCount, 2)) {
        hand.type = ONE_PAIR;
        addRankValuesForNOfAKind(rankCount, 2);
    } 
    else {
        hand.type = HIGH_CARD;
        for (int i = 0; i < hand.cards.size(); ++i)
            // Highest cards
            rankValues.push_back(hand.cards[i].rank); 
    }
}

#endif