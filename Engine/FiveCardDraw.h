#pragma once

#include <chrono>
#include <deque>
#include <iostream>
#include <thread>
#include <vector>

#include "CLI.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include "PokerEngine.h"
#include "PokerGameplay.h"
#include "Random.h"

void replaceCards(std::vector<Player>& players, int orderPlayer, Deck& deck, const std::vector<int>& cardsToRemove) {
    // Removing cards from player's hand
    auto Card = players[orderPlayer].hand.cards;
    std::vector<int> removedCards;

    // Loại bỏ các lá bài dựa trên chỉ số trong cardsToRemove
    for (int i = cardsToRemove.size() - 1; i >= 0; --i) { // Duyệt từ cuối về đầu
        int index = cardsToRemove[i];
        if (index >= 0 && index < 5) {
            removedCards.push_back(Card[index]);
            players[orderPlayer].hand.erase(Card[index]); // Xóa lá bài bằng chỉ số
        }
        else {
            std::cout << "Invalid index: " << index << " in cardsToRemove, skipping." << std::endl;
        }
    }

    // Add removed card to deck
    for (int card : removedCards) {
        deck.addCard(card, removedCards.size());
    }

    // Shuffle deck
    deck.shuffle();

    // Draw exactly the number of card has been removed (Example: Removed 3 cards so draw 3 cards)
    int numToDraw = removedCards.size();
    for (int i = 0; i < numToDraw; i++)
        players[orderPlayer].hand.add(deck.draw());
}

// Phase 1 allow every player to draw their cards
void Phase1(std::vector<Player>& players, std::deque<int>& playerOrder, Deck& deck) {
    // Shuffle card
    deck.shuffle();

    // Get the sleep time and annouce 
    std::cout << "Dealing cards ...";
    CLI::sleep(2000);

    // Clear screen and start the game
    CLI::clearScreen();

    // Main processor of phase 1
    int playerCount = players.size();
    for (int i = 0; i < playerCount; i++) {
        std::cin.clear();
        // Deal card
        for (int j = 0; j < 5; j++) {
            players[playerOrder.front()].hand.add(deck.draw());
        }

        // Print the current player's hand
        std::cout << "Player " << players[playerOrder.front()].name << "'s turn " << std::endl;
        std::cout << "Your hand: " << players[playerOrder.front()].hand.toString() << std::endl;

        // Get the player option
        std::cout << "Do you want to draw? ";
        bool action = CLI::getOptionYN();

        // Check the player action
        if (action) {
            // Get the number of removing cards
            int number = 0;
            std::cout << "Choose number of cards to remove ";
            number = CLI::getOptionNum(1, 5);
            std::cout << std::endl;

            // Get the index of the removing card
            std::vector<int> cardsToRemove;
            std::cout << "Enter the index of the card you want to remove: (1 - 5) " << std::endl;
            bool visit[12];
            for (int i = 0; i < 12; i++)
                visit[i] = false;
            // Removing cards
            for (int j = 0; j < number; j++) {
                int temp = 0;
                std::cin >> temp;
                if (!visit[temp]) {
                    visit[temp] = true;
                    cardsToRemove.push_back(temp - 1);
                }
                else {
                    std::cout << "Can not choose the an index more than one time" << std::endl;
                    j--;
                }
            }
            for (int i = 0; i < 12; i++)
                visit[i] = false;

            // Ignore \n
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');

            // Replacing cards
            replaceCards(players, i, deck, cardsToRemove);
        }

        // Change to the next player
        dequeNext(playerOrder);
        std::cout << "You have finished your turn. It's time for another player...";
        CLI::sleep(5000);
        CLI::clearScreen();
        CLI::sleep(2000);
    }
}

// Phase 2: Players will have bet round and showdown
void Phase2(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot) {
    // Re-use the bet function
    studPokerBetRound(players, playerOrder, 5, 0, pot, 0);

    // Showdown cards
    showdown(players, playerOrder, pot);
}