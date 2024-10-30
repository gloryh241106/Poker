#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

// Hand
#include <random>
#include <algorithm>
#include "Card_Deck.h"
#include "Comparison.h"

struct Hand {
    std::vector<Card> cards;
    int type;
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

    void sort(int n){
        for (int i = 0; i < n - 1; i++) {
            int min_index = i;

            for (int j = i + 1; j < n; j++) {
                if (cards[min_index].rank >= cards[j].rank) 
                    if (cards[min_index].suit > cards[j].suit) 
                        min_index = j;
            }

            std::swap (cards[i], cards[min_index]);
        }
    }

    void deal(int n) {
        for (int i = 0; i < n; i++) {
            Card temp = deck.back();
            cards.push_back(temp);
            deck.pop_back();
        }

        sort(n);
    }
};

#endif