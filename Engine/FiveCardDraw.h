﻿#pragma once

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
    std::vector<int> removedCards;
    for (int card : cardsToRemove) {
        auto& hand = players[orderPlayer].hand;
        auto it = std::find(std::begin(hand.cards), std::end(hand.cards), card);
        if (it != std::end(hand.cards)) {
            removedCards.push_back(card);
            hand.erase(card);
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

void BackTrackingBet(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot, int& highestBet, int i) {
    for (int j = 0; j < i; j++) {
        Player& PrevPlayer = players[playerOrder[j]];
        if (!PrevPlayer.folded || !PrevPlayer.allIn) {
            std::cout << PrevPlayer.name << ", Current bet: " << highestBet
                      << ", Your chips: " << PrevPlayer.chips << std::endl;
            std::cout << "Choose your action: " << std::endl;
            std::cout << "[1] Fold, [2] Call, [3] All in" << std::endl;

        // Get player's choice
        BacktrackingChoose:
            int Choose;
            std::cin >> Choose;

            // Checking player's choice
            if (Choose != 1 || Choose != 2 || Choose != 3 || std::cin.fail()) {
                std::cout << "Invalid Input, choose from 1 to 3" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                goto BacktrackingChoose;
            }

            switch (Choose) {
                case 1:
                    PrevPlayer.folded = true;
                    break;
                case 2: {
                    int callAmount = highestBet - PrevPlayer.bet;
                    if (callAmount > PrevPlayer.chips)
                        callAmount = PrevPlayer.chips;
                    PrevPlayer.chips -= callAmount;
                    PrevPlayer.bet += callAmount;
                    pot += callAmount;
                } break;
                case 3: {
                    pot += PrevPlayer.chips;
                    PrevPlayer.bet += PrevPlayer.chips;
                    PrevPlayer.chips = 0;
                    PrevPlayer.allIn = true;
                    highestBet = std::max(highestBet, PrevPlayer.bet);
                } break;
            }
        }
    }
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
        std::cout << "Player " << playerOrder.front() << "'s turn " << std::endl;
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

            // Removing cards
            for (int j = 0; j < number; j++) {
                int temp = 0;
                std::cin >> temp;
                cardsToRemove.push_back(temp); 
            }

            // Replacing cards
            replaceCards(players, i, deck, cardsToRemove);
        }

        // Change to the next player
        dequeNext(playerOrder);
        std::cout << "You have finished your turn. It's time for another player...";
        CLI::sleep(5000);
        CLI::clearScreen();
    }
}

// Phase 2: Players will have bet round and showdown
void Phase2(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot) {
    bool bettingRound = true;
    int highestBet = 0;

    while (bettingRound) {
        for (int i = 0; i < playerOrder.size(); i++) {
            Player& currentPlayer = players[playerOrder[i]];

            // // Print the current player's hand
            // std::cout << "Player " << playerOrder.front() << "'s turn " << std::endl;
            // std::cout << "Your hand: " << players[playerOrder.front()].hand.toString() << std::endl;

            // std::cout << currentPlayer.name << ", Current bet: " << highestBet
            //           << ", Your chips: " << currentPlayer.chips << std::endl;

        // reinput:
        //     if (highestBet == 0) {
        //         std::cout << "Actions: [1] FOLD, [2] CHECK, [4] BET, [6] ALL IN " << std::endl;
        //     } else {
        //         std::cout << "Actions: [1] FOLD, [3] CALL, [5] RAISE, [6] ALL IN" << std::endl;
        //     }

        //     // Get the player's action
        //     int action = CLI::getOneNumber(1, 5);

            // Betting
            studPokerBetRound(players, playerOrder, 5, 0, pot, 0);
            // switch (action) {
            //     case 1:  // Fold
            //         currentPlayer.folded = true;
            //         break;

            //     case 2:  // Check
            //         if (highestBet != 0) {
            //             std::cout << "You cannot check, you need to call or raise." << std::endl;
            //             --i;  // Repeat turn
            //         }
            //         break;

            //     case 3:  // Call
            //         {
            //             int callAmount = highestBet - currentPlayer.bet;
            //             if (callAmount > currentPlayer.chips)
            //                 callAmount = currentPlayer.chips;
            //             currentPlayer.chips -= callAmount;
            //             currentPlayer.bet += callAmount;
            //             pot += callAmount;
            //         } 
            //         break;

            //     case 4:  // Bet
            //         {
            //             if (highestBet != 0) {
            //                 std::cout << "You are not allow to bet, please choose "
            //                             "another action"
            //                         << std::endl;
            //                 --i;
            //             } else {
            //                 int betAmount;
            //                 std::cout << "Enter bet amount: ";
            //                 std::cin >> betAmount;

            //                 if (betAmount > currentPlayer.chips || betAmount <= 0) {
            //                     std::cout << "Invalid bet amount." << std::endl;
            //                     --i;
            //                     break;
            //                 }

            //                 currentPlayer.chips -= betAmount;
            //                 currentPlayer.bet += betAmount;
            //                 pot += betAmount;
            //                 highestBet = std::max(highestBet, currentPlayer.bet);
            //                 BackTrackingBet(players, playerOrder, pot, highestBet, i);
            //                 break;
            //             }
            //         }

            //     case 5:  // Raise
            //         {
            //             int raiseAmount;
            //             std::cout << "Enter raise amount: ";
            //             std::cin >> raiseAmount;

            //             int totalBet = raiseAmount + highestBet;
            //             if (totalBet > currentPlayer.chips)
            //                 totalBet = currentPlayer.chips;

            //             currentPlayer.chips -= totalBet;
            //             currentPlayer.bet += totalBet;
            //             pot += totalBet;
            //             highestBet = std::max(highestBet, currentPlayer.bet);
            //             BackTrackingBet(players, playerOrder, pot, highestBet, i);
            //         } 
            //         break;

            //     case 6:  // All-in
            //         {
            //             pot += currentPlayer.chips;
            //             currentPlayer.bet += currentPlayer.chips;
            //             currentPlayer.chips = 0;
            //             currentPlayer.allIn = true;
            //             highestBet = std::max(highestBet, currentPlayer.bet);
            //             BackTrackingBet(players, playerOrder, pot, highestBet, i);
            //         }
            //         break;
                    
            // }
        }
        bettingRound = false;
    }

    // Showdown cards
    showdown(players, playerOrder, pot);
}
