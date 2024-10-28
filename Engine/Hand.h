#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

// Hand
#include <random>
#include <algorithm>
#include "Card.h"
#include "Comparison.h"

class Hand {
    public:
        std::vector<Card> cards;
        HandType type;

        bool concat(std::vector<Card> cards) {
            
        }

        std::string toString(std::vector<Card> cards) {
            for (int i = 0; i < cards.size(); i++) {
                std::cout << cards[i].to_string();
            }
        }

        Hand() {
            std::sort(cards.begin(), cards.end());
        }
};

#endif