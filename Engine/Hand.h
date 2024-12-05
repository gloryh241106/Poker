#ifndef __ENGINE_INIT_POKER__
#define __ENGINE_INIT_POKER__

// Hand
#include <algorithm>
#include <random>
#include "Card.h"

class Hand {
private:
    uint8_t cardMask = 0x00;
    uint64_t handBit = 0x0000000000000000;
    //                      AKQJT98765432

public:
    int cards[5] = {-1, -1, -1, -1, -1};
    int size = 0;

    bool add(int card) {
        if (size >= 5) return false;

        cards[size] = card;
        int t = size;
        size++;
        handBit |= 1LL << card;

        return true;
    }

    uint64_t& bit() { return handBit; }
    const uint64_t& bit() const { return handBit; }

    uint32_t compressedBit() const {
        uint32_t compressed = 0;
        for (int i = 0; i < 13; i++) {
            int count = __builtin_popcountll(handBit & (0xfull << (i << 2)));
            compressed |= count << (i << 1);
        }

        return compressed;
    }

    void clear() {
        handBit = 0x0ull;
        size = 0;
        for (int i = 0; i < 5; i++) {
            cards[i] = -1;
        }
    }
    
    void erase(int card) {
        int index = -1;
        int size1 = 5;
        for (int i = 0; i < size1; i++)
            if (cards[i] == card)
                index = i;

        if (index == -1)
            std::cout << "Can not find your card" << std::endl;
        for (int i = index; i < size1 - 1; i++)
            cards[i] = cards[i + 1];
        size1--;
    }

    void setMask(uint8_t mask) { cardMask = mask; }
    void clearMask() { cardMask = 0x00; }

    std::string toString(bool applyMask = false) const {
        std::string handString;

        for (int i = 0; i < 5; i++) {
            if (!applyMask || !(cardMask & (1 << i)))
                handString += cardToString(cards[i]);
            else
                handString += "XX";
            if (i != 4) handString += ' ';
        }

        return handString;
    }
};

#endif