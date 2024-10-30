#ifndef __ENGINE_COMPARISON__
#define __ENGINE_COMPARISON__

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include "Card_Deck.h"
#include "PokerEngine.h"

// Enum for representing HandType

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

// Vector for storing result 
std::vector<int> rankValues;

//Counting how many times each rank appers in hands
std::map<int, int> getRankCounts(std::vector<Card> &hands) {
    // Map for storing each rank appears
    std::map<int, int> rankCount;

    // Counting
    for (int i = 0; i < hands.size(); i++) {
        rankCount[hands[i].rank]++;
    }

    // Return result
    return rankCount;
}

bool isFlushHand(std::vector<Card> &hands) {
    // The first suit
    int firstSuit = hands[0].suit;

    // Checking if hands is not Flush
    for (int i = 1; i < hands.size(); i++) {
        if (hands[i].suit != firstSuit) 
            return false;
    }

    // Return true if hands is Flush
    return true;
}

bool isStraightHand(std::vector<Card> &hands) {
    // Checking if hands is not Straight
    for (int i = 1; i < hands.size(); i++) {
        if (hands[i].rank != hands[i - 1].rank + 1)
            return false;
    }

    // Return true if hands is Straight
    return true;
}

//-------------------- N of a kind -----------------------------------

// Checking if the hand has N of a kind (N = 4, N = 3)
bool has_N_Kind(std::map<int, int> &rankCount, int n) {
    // Temporary map iterator
    std::map<int, int>::iterator temp;    

    // Checking each element using temp
    for(temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == n)
            return true;
    } 
    
    // Return false if not found
    return false;
}

// Add rank values for hands with N of a kind if there are N of a kind
void addRankValuesForNOfAKind(std::map<int, int> &rankCount, int n) {
    // Temporary map
    std::map<int, int>::iterator temp;

    // Add Rank value if temp->second (which is the number of cards) is equal to n
    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == n) rankValues.push_back(temp->first);
    }

    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second != n) rankValues.push_back(temp->first);
    }
}

//-------------------- Full House -----------------------------------

bool hasFullHouse(std::map<int, int> &rankCount) {
    bool three = false, two = false;

    // Temporary iterator
    std::map<int, int>::iterator temp;
    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        // Checking three
        if (temp->second == 3) 
            three = true;

        // Checking two
        if (temp->second == 2) 
            two = true;
    }

    // Return true if have both three and two
    return three && two;
}

// Add rank values for full house (three of a kind + pair) if there are full house
void addRankValuesForFullHouse(std::map<int, int> &rankCount) {
    // Temporary iterator
    std::map<int, int>::iterator temp;

    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == 3) rankValues.push_back(temp->first);
    }

    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == 2) rankValues.push_back(temp->first);
    }
}

//-------------------- Two Pairs -----------------------------------

// Check if the hand has two pairs
bool hasTwoPairs(std::map<int, int> &rankCount) {
    // Int pairCount for checking 
    int pairCount = 0;

    // Counting pairs in hand
    std::map<int, int>::iterator temp;
    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == 2) 
            pairCount++;
    }

    // Return true if have two pairs, else return false
    return pairCount == 2;
}

// Add rank values for two pair if there are 2 pairs
void addRankValuesForTwoPairs(std::map<int, int> &rankCount) {
    // Initialize a vector for storing pairs
    std::vector<int> pairs;

    // Initialize an integer for storing the card (Use for High Card)
    int otherCard = 0;

    // Initialize temporarity map
    std::map<int, int>::iterator temp;

    // Checking and adding to vector
    for (temp = rankCount.begin(); temp != rankCount.end(); temp++) {
        if (temp->second == 2) pairs.push_back(temp->first);
        if (temp->second == 1) otherCard = temp->first;
    }

    // Sort pairs in descending order
    sort(pairs.rbegin(), pairs.rend()); 
    rankValues.insert(rankValues.end(), pairs.begin(), pairs.end());
    rankValues.push_back(otherCard);
}

// Nguyên sẽ làm phần so sánh bài Xì dách
//...

#endif