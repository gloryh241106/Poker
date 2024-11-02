#ifndef __ENGINE_COMPARISON__
#define __ENGINE_COMPARISON__

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include "Card_Deck.h"
#include "PokerEngine.h"

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
    // A vector for storing pairs
    std::vector<int> pairs;

    // Integer for storing the card (Use for High Card)
    int otherCard = 0;

    // Temporarity map
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

void reset_rankValues(std::vector<int> &rankValues) {
    rankValues.clear();
}

void reset_rankCount(std::map<int, int> &rankCount) {
    rankCount.clear();
}

//_________________BLACK JACK _______________________

struct Result {
    int Error = -1;
    int Upper_Case = 0;
    int NguLinh = 22;
    int Black_Jack = 23;
    int Pair_Aces = 24;
};

const Result result;

int Last_Hope(int& temp, int idx, int arr[]) {
    if (idx == -1) return temp;
    if (temp > 21) {
        temp -= arr[idx];
        idx--;
        temp += arr[idx];
        Last_Hope(temp, idx, arr);
    }
    return temp;
}

// Ham truyen vao Vector chua cac la bai va return lai gia tri so sanh (Cu the coi struct).
int Calculate_Hands_Value(std::vector<char> hand) {
    int Hand_Value = 0;
    int Count_Ace = 0;
    int Ace_Value[3] = { 1, 10, 11 };

    for (auto idx : hand) { 
        // In case Value {10, J, Q, K}
        if (idx == 'T' || idx == 'J' || idx == 'Q' || idx == 'K') 
            Hand_Value += 10;
        // In case Value {A}
        else if (idx == 'A') { 
            if (Count_Ace == 0) {
                Hand_Value += 11;
                Count_Ace++;
            } else {
                Hand_Value += 1;
                Count_Ace++;
            }
        } else {  //In case Value 1->9      
            int Value = static_cast<int>(idx);
            if (hand.size() >= 2 && Value >= 49 && Value <= 57)
                Hand_Value = Hand_Value + (Value - 48);
        }
    }

    // If has more than 2 Ace cards
    if (Count_Ace >= 2) 
        Hand_Value -= 10;

    // Special cases
    if (hand.size() == 2) { 
        if (Hand_Value == 21) 
            return result.Black_Jack;
        if (Count_Ace == 2)
            return result.Pair_Aces;
    }
    if (hand.size() == 5 && Hand_Value <= 21)
        return result.NguLinh;

    // Recalculate the Value of hand that has Ace
    if (Hand_Value > 21 && Count_Ace == 1 && hand.size() <= 3)
        Last_Hope(Hand_Value, 2, Ace_Value);

    // Normal Hand_Value case
    if (Hand_Value >= 16 && Hand_Value <= 21)
        return Hand_Value;

   // In case Hand_Value is higher than 21
    if (Hand_Value > 21 && Hand_Value < 28)
        return result.Upper_Case;

    // In case Hand_Value is smaller than 16
    if (Hand_Value < 16 || Hand_Value >= 28)
        return result.Error;

    return -2;
}


#endif