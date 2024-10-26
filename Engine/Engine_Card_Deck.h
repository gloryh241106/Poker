#ifndef __ENGINE_CARD_DECK__
#define __ENGINE_CARD_DECK__

#include <algorithm>
#include <vector>
#include <ctime>
#include <iostream>
#include <random>

// Enum for Suit
enum Suit {
    SPADES,
    CLUBS,
    DIAMOND,
    HEARTS
};

//Enum for Rank
enum Rank {
    TWO = 2, 
    THREE, 
    FOUR, 
    FIVE, 
    SIX, 
    SEVEN, 
    EIGHT, 
    NINE, 
    TEN, 
    JACK, 
    QUEEN, 
    KING, 
    ACE
};

// Create a struct for each card
struct Card {
    Rank rank;
    Suit suit;

    void print() {
        std::string rank_str[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::string suit_str[] = {"Spades", "Clubs", "Diamond", "Hearts"};
        std::cout << rank_str[rank - 2] << " of " << suit_str[suit] << std::endl;
    }
};

// Create a deck
class Deck {
public:
    // Calling Deck for initialize a random deck
    Deck() {
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

        // Shuffle the deck
        std::shuffle(deck.begin(), deck.end(), rng);
        std::shuffle(deck.begin(), deck.end(), rng);
        std::shuffle(deck.begin(), deck.end(), rng);
    }

    // Draw a card
    Card dealCard() {
        // Make a card
        Card dealtCard = deck.back();

        // Remove the card from the deck
        deck.pop_back();

        //Return the card
        return dealtCard;
    }

private:
    std::vector<Card> deck;
};

#endif