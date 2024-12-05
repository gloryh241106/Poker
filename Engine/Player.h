#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "Hand.h"

struct Player {
    Hand hand;
    std::string name;
    int chips;
    int bet;
    bool folded;
    bool lost;
    bool allIn;
    int showdownBet = 0;
};

#endif