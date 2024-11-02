#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

// Hand
#include <random>
#include <algorithm>
#include "Card_Deck.h"
#include "Comparison.h"

struct Hand {
    int player_index;
    std::vector<Card> cards;
    int type;
    
    Card highest_card_type;
    int ranking_match;

    bool concat(Card &card) {
        for(auto temp : cards) {
            if (temp.rank == card.rank && temp.suit == card.suit)
                return true;
        }

        return false;
    }

    std::vector<std::string> toString() {
        std::vector<std::string> hand_string;

        for (int i = 0; i < cards.size(); i++) {
            hand_string.push_back(cards[i].to_string());
        }

        return hand_string;
    }

    void deal(int n) {
        for (int i = 0; i < n; i++) {
            Card temp = deck.back();
            cards.push_back(temp);
            deck.pop_back();
        }

        std::sort(cards.begin(), cards.end());
    }
};

#endif