#ifndef __PLAYER__
#define __PLAYER__

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
};

#endif