#pragma once

#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

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
#include "Random.h"

void replaceCards(std::vector<Player>& players, int orderPlayer, Deck& deck,
                  const std::vector<int>& cardsToRemove) {
    // removing cards from player hand
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

    // Draw exactly the number of card has been removed (example: removed 3
    // cards so draw 3 cards)
    int numToDraw = removedCards.size();
    for (int i = 0; i < numToDraw; i++)
        players[orderPlayer].hand.add(deck.draw());
}

void BackTrackingBet(std::vector<Player>& players, std::deque<int>& playerOrder,
                     int& pot, int& highestBet, int i) {
    for (int j = 0; j < i; j++) {
        Player& PrevPlayer = players[playerOrder[j]];
        if (!PrevPlayer.folded || !PrevPlayer.allIn) {
            std::cout << PrevPlayer.name << ", Current bet: " << highestBet
                      << ", Your chips: " << PrevPlayer.chips << std::endl;
            std::cout << "Choose your action: [1] Fold, [2] Call, [3] All in"
                      << std::endl;

        BacktrackingChoose:
            int Choose;
            std::cin >> Choose;

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
void Phase1(std::vector<Player>& players, std::deque<int>& playerOrder,
            Deck& deck) {
    // Shuffle card
    deck.shuffle();

    // Deal card for each players   
    int playerCount = players.size();
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < 5; j++) {
            players[playerOrder.front()].hand.add(deck.draw());
        }
        dequeNext(playerOrder);
    }
    TryAgain:
        //  Check and allow draw card
<<<<<<< HEAD
    for (int i = 0; i < playerCount; ++i) {
        //Player& currentPlayer = players[i];
        std::cout << "CurrentPlayer is player " << i << std::endl;
        std::cout << "Do you want to draw? (Y/N) " << std::endl;
        char action;
        std::cin >> action;

        if (toupper(action) == 'Y') {
            int number = 0;
            do {
                std::cout << "Choose number of cards to remove (1 to 5): " << std::endl;
                std::cin >> number;

                if (number < 1 || number > 5 || std::cin.fail()) {
                    std::cout << "Invalid number. Please choose between 1 and 5." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    continue;
                }

                std::vector<int> cardsToRemove;
                std::cout << "Enter the card values to remove: " << std::endl;
                for (int j = 0; j < number; j++) {
                InputCardValueToRemove:
                    int cardValue;
                    std::cin >> cardValue;

                    if (!std::cin.fail())
                        cardsToRemove.push_back(cardValue);
                    else {
                        std::cout << "Invalid output, enter again" << std::endl;
=======
        for (int i = 0; i < playerCount; ++i) {
            // Player& currentPlayer = players[i];
            std::cout << "CurrentPlayer is player " << i << std::endl;
            std::cout << "Do you want to draw? (Y/N) " << std::endl;
            char action;
            std::cin >> action;

            if (toupper(action) == 'Y') {
                int number = 0;
                do {
                    std::cout << "Choose number of cards to remove (1 to 5): "
                              << std::endl;
                    std::cin >> number;

                    if (number < 1 || number > 5 || std::cin.fail()) {
                        std::cout
                            << "Invalid number. Please choose between 1 and 5."
                            << std::endl;
>>>>>>> 25d84c07e700e6927e8fddefe76398d50833b9b2
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        goto InputCardValueToRemove;
                    }
<<<<<<< HEAD
                }
                replaceCards(players, i, deck, cardsToRemove);
            } while (number < 1 || number > 5 || std::cin.fail());
        }
        else if (toupper(action) == 'N') continue;
        else {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
            goto TryAgain;
=======

                    std::vector<int> cardsToRemove;
                    std::cout << "Enter the card values to remove: "
                              << std::endl;
                    for (int j = 0; j < number; j++) {
                    InputCardValueToRemove:
                        int cardValue;
                        std::cin >> cardValue;

                        if (!std::cin.fail())
                            cardsToRemove.push_back(cardValue);
                        else {
                            std::cout << "Invalid output, enter again"
                                      << std::endl;
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            goto InputCardValueToRemove;
                        }
                    }
                    replaceCards(players, i, deck, cardsToRemove);
                } while (number < 1 || number > 5 || std::cin.fail());
            } else if (toupper(action) == 'N')
                continue;
            else {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                goto TryAgain;
            }
>>>>>>> 25d84c07e700e6927e8fddefe76398d50833b9b2
        }
    }
}

void Phase2(std::vector<Player>& players, std::deque<int>& playerOrder,
            int& pot) {
    bool bettingRound = true;
    int highestBet = 0;

    while (bettingRound) {
        for (int i = 0; i < playerOrder.size(); i++) {
            Player& currentPlayer = players[playerOrder[i]];

            // if (currentPlayer.folded || currentPlayer.allIn) continue;

            std::cout << currentPlayer.name << ", Current bet: " << highestBet
                      << ", Your chips: " << currentPlayer.chips << std::endl;

        reinput:

            if (highestBet == 0) {
                std::cout
                    << "Actions: [1] FOLD, [2] CHECK, [4] BET, [6] ALL IN "
                    << std::endl;
            } else {
                std::cout
                    << "Actions: [1] FOLD, [3] CALL, [5] RAISE, [6] ALL IN"
                    << std::endl;
            }

            int action;
            std::cin >> action;
            if (std::cin.fail() || action > 5 || action < 1) {
                std::cout << "Invalid input, try again" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                goto reinput;
            }

            switch (action) {
                case 1:  // Fold
                    currentPlayer.folded = true;
                    break;

                case 2:  // Check
                    if (highestBet != 0) {
                        std::cout
                            << "You cannot check, you need to call or raise."
                            << std::endl;
                        --i;  // Repeat turn
                    }
                    break;

                case 3:  // Call
                {
                    int callAmount = highestBet - currentPlayer.bet;
                    if (callAmount > currentPlayer.chips)
                        callAmount = currentPlayer.chips;
                    currentPlayer.chips -= callAmount;
                    currentPlayer.bet += callAmount;
                    pot += callAmount;
                } break;

                case 4:  // Bet
                {
                    if (highestBet != 0) {
                        std::cout << "You are not allow to bet, please choose "
                                     "another action"
                                  << std::endl;
                        --i;
                    } else {
                        int betAmount;
                        std::cout << "Enter bet amount: ";
                        std::cin >> betAmount;

                        if (betAmount > currentPlayer.chips || betAmount <= 0) {
                            std::cout << "Invalid bet amount." << std::endl;
                            --i;
                            break;
                        }

                        currentPlayer.chips -= betAmount;
                        currentPlayer.bet += betAmount;
                        pot += betAmount;
                        highestBet = std::max(highestBet, currentPlayer.bet);
                        BackTrackingBet(players, playerOrder, pot, highestBet,
                                        i);
                        break;
                    }
                }
                case 5:  // Raise
                {
                    int raiseAmount;
                    std::cout << "Enter raise amount: ";
                    std::cin >> raiseAmount;

                    int totalBet = raiseAmount + highestBet;
                    if (totalBet > currentPlayer.chips)
                        totalBet = currentPlayer.chips;

                    currentPlayer.chips -= totalBet;
                    currentPlayer.bet += totalBet;
                    pot += totalBet;
                    highestBet = std::max(highestBet, currentPlayer.bet);
                    BackTrackingBet(players, playerOrder, pot, highestBet, i);
                } break;

                case 6:  // All-in
                {
                    pot += currentPlayer.chips;
                    currentPlayer.bet += currentPlayer.chips;
                    currentPlayer.chips = 0;
                    currentPlayer.allIn = true;
                    highestBet = std::max(highestBet, currentPlayer.bet);
                    BackTrackingBet(players, playerOrder, pot, highestBet, i);
                } break;
            }
        }
        bettingRound = false;
    }
    showdown(players, playerOrder, pot);
}

#endif