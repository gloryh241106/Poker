#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

#include <chrono>
#include <deque>
#include <iostream>
#include <thread>
#include <vector>

#include "CLI.h"
#include "Card.h"
#include "Random.h"
// #include "Engine/Game.h"
#include "Hand.h"
#include "PokerEngine.h"
// #include "Engine/XiDachEngine.h"

enum PlayerAction { NONE, CHECK, CALL, BET, RAISE, FOLD, ALL_IN };

struct Player {
    Hand hand;
    std::string name;
    int chips;
    int bet;
    bool folded;
    bool lost;
    bool allIn;
    PlayerAction action = NONE;
    int showdownBet = 0;
};

void dequeNext(std::deque<int>& q) {
    int front = q.front();
    q.pop_front();
    q.push_back(front);
}

void replaceCards(std::vector<Player>& players, int orderPlayer, Deck& deck, const std::vector<int>& cardsToRemove) {
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

    // Draw exactly the number of card has been removed (example: removed 3 cards so draw 3 cards)
    int numToDraw = removedCards.size();
    for (int i = 0; i < numToDraw; i++) 
        players[orderPlayer].hand.add(deck.draw());
      
    
}

void BackTrackingBet(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot, int& highestBet, int i) {
    for (int j = 0; j < i; j++) {
        Player& PrevPlayer = players[playerOrder[j]];
        if (!PrevPlayer.folded || !PrevPlayer.allIn) {
            std::cout << PrevPlayer.name << ", Current bet: " << highestBet << ", Your chips: " << PrevPlayer.chips << std::endl;
            std::cout << "Choose your action: [1] Fold, [2] Call, [3] All in" << endl;

        BacktrackingChoose:
            int Choose;
            cin >> Choose;
            if (Choose != 1 || Choose != 2 || Choose != 3 || cin.fail()) {
                cout << "Invalid Input, choose from 1 to 3" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto BacktrackingChoose;
            }
            switch (Choose) {
                case 1: {
                    PrevPlayer.folded = true;
                    break;
                }
                case 2: {
                    int callAmount = highestBet - PrevPlayer.bet;
                    if (callAmount > PrevPlayer.chips) callAmount = PrevPlayer.chips;
                    PrevPlayer.chips -= callAmount;
                    PrevPlayer.bet += callAmount;
                    pot += callAmount;
                }
                      break;
                case 3: {
                    pot += PrevPlayer.chips;
                    PrevPlayer.bet += PrevPlayer.chips;
                    PrevPlayer.chips = 0;
                    PrevPlayer.allIn = true;
                    highestBet = max(highestBet, PrevPlayer.bet);
                }
                      break;
            }
        }
    }
}
//Phase1 allow every player to draw their cards
void Phase1(std::vector<Player>& players, std::deque<int>& playerOrder, Deck& deck) {
    // shuffle card
    deck.shuffle();

    // Deal card for each players
    int playerCount = players.size();
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < 5; j++) {
            players[playerOrder.front()].hand.add(deck.draw());
        }
    TryAgain:
        //  Check and allow draw card
        for (int i = 0; i < playerCount; ++i) {
            //Player& currentPlayer = players[i];
            cout << "CurrentPlayer is player " << i << endl;
            std::cout << "Do you want to draw? (Y/N) " << endl;
            char action;
            std::cin >> action;

            if (toupper(action) == 'Y') {
                int number = 0;
                do {
                    std::cout << "Choose number of cards to remove (1 to 5) " << endl;
                    std::cin >> number;

                    if (number < 1 || number > 5 || cin.fail()) {
                        std::cout << "Invalid number. Please choose between 1 and 5." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        continue;
                    }

                    std::vector<int> cardsToRemove;
                    std::cout << "Enter the card values to remove " << endl;
                    for (int j = 0; j < number; j++) {
                    InputCardValueToRemove:
                        int cardValue;
                        std::cin >> cardValue;
                        if(!cin.fail())
                            cardsToRemove.push_back(cardValue);
                        else {
                            cout << "Invalid output, enter again" << endl;
                            cin.clear();
                            std::cin.ignore(1000, '\n');
                            goto InputCardValueToRemove;
                        }
                    }
                    replaceCards(players, i, deck, cardsToRemove);
                } while (number < 1 || number > 5 || cin.fail());
            }

            else if (toupper(action) == 'N')  continue;
           
            else {
                cin.clear();
                std::cin.ignore(1000, '\n'); 
                goto TryAgain;
            }
        }
        dequeNext(playerOrder);
    }
 }
void showdown(std::vector<Player>& player, std::deque<int>& playerOrder, int& pot) {
    // int pot = 0;
    int playerCount = playerOrder.size();
    for (int i : playerOrder) {
        // std::cout << "Here " << p.bet << std::endl;
        // CLI::getEnter();
        // pot += p.bet;
        // p.chips -= p.bet;
        if (player[i].folded) continue;
        PokerEngine::eval(player[i].hand.bit());
    }

    std::vector<int> playerRank(playerOrder.begin(), playerOrder.end());

    // Sort the players by hand strength
    std::sort(playerRank.begin(), playerRank.end(), [&](int a, int b) {
        return PokerEngine::compareHands(player[a].hand, player[b].hand);
        });

    // Display the hands
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Showdown" << std::endl;
    for (int i = 0; i < playerCount; i++) {
        if (player[playerRank[i]].folded) continue;
        std::cout << "Player " << playerRank[i]
            << "'s hand: " << player[playerRank[i]].hand.toString()
            << " (" << PokerEngine::type(player[playerRank[i]].hand)
            << ")" << std::endl;
    }
    for (int i : playerRank) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // Distribute the pot
    int i = 0;
    while (i < playerCount && pot > 0) {
        player[playerRank[i]].showdownBet = std::min(
            pot, player[playerRank[i]].showdownBet * (playerCount - i));
        player[playerRank[i]].chips += player[playerRank[i]].showdownBet;
        pot -= std::min(pot,
            player[playerRank[i]].showdownBet * (playerCount - i));
        i--;
    }

    // Display the chips
    for (int i = 0; i < playerCount; i++) {
        std::cout << "Player " << i << " has " << player[i].chips << " chips"
            << std::endl;
    }

    // Remove lost players
    i = 0;
    while (i < playerOrder.size()) {
        if (player[playerOrder.front()].chips == 0) {
            player[playerOrder.front()].lost = 1;
            playerOrder.pop_front();
            continue;
        }
        dequeNext(playerOrder);
        i++;
    }

    // Reset the players
    for (int i : playerOrder) {
        player[i].hand.clear();
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].allIn = 0;
        player[i].showdownBet = 0;
    }
    CLI::getEnter();
}
void Phase2(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot) {
    bool bettingRound = true;
    int highestBet = 0;

    while (bettingRound) {
        for (int i = 0; i < playerOrder.size(); i++) {
            Player& currentPlayer = players[playerOrder[i]];

            //if (currentPlayer.folded || currentPlayer.allIn) continue;

            std::cout << currentPlayer.name << ", Current bet: " << highestBet << ", Your chips: " << currentPlayer.chips << std::endl;
        
        reinput: 

            if (highestBet == 0) {
                std::cout << "Actions: [1] Check, [2] Bet, [3] Fold, [4] All in" << std::endl;
            }
            else {
                std::cout << "Actions: [1] Call, [2] Raise, [3] Fold, [4] All in" << std::endl;
            }

            int action;
            std::cin >> action;
            if (cin.fail() || action > 5 || action < 1) {
                cout << "Invalid input, try again" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto reinput;
            }

            switch (action) {
                case 1:  // Fold
                    currentPlayer.folded = true;
                    break;

                case 2:  // Check
                    if (highestBet != 0) {
                        std::cout << "You cannot check, you need to call or raise." << std::endl;
                        --i;  // Repeat turn
                    }
                    break;

                case 3:  // Call
                {
                    int callAmount = highestBet - currentPlayer.bet;
                    if (callAmount > currentPlayer.chips) callAmount = currentPlayer.chips;
                    currentPlayer.chips -= callAmount;
                    currentPlayer.bet += callAmount;
                    pot += callAmount;
                }
                break;

                case 4:  // Bet
                {
                    if (highestBet != 0) {
                        std::cout << "You are not allow to bet, please choose another action" << std::endl;
                        --i;
                    }
                    else {
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
                        highestBet = max(highestBet, currentPlayer.bet);
                        BackTrackingBet(players, playerOrder, pot, highestBet, i);
                        break;
                    }
                }
                case 5:  // Raise
                {
                    int raiseAmount;
                    std::cout << "Enter raise amount: ";
                    std::cin >> raiseAmount;

                    int totalBet = raiseAmount + highestBet;
                    if (totalBet > currentPlayer.chips) totalBet = currentPlayer.chips;

                    currentPlayer.chips -= totalBet;
                    currentPlayer.bet += totalBet;
                    pot += totalBet;
                    highestBet = max(highestBet, currentPlayer.bet);
                    BackTrackingBet(players, playerOrder, pot, highestBet, i);
                }
                break;

                case 6:  // All-in
                {    pot += currentPlayer.chips;
                    currentPlayer.bet += currentPlayer.chips;
                    currentPlayer.chips = 0;
                    currentPlayer.allIn = true;
                    highestBet = max(highestBet, currentPlayer.bet);
                    BackTrackingBet(players, playerOrder, pot, highestBet, i);
                }
                break;
            }
        }
        bettingRound = false;
    }
    showdown(players, playerOrder, pot);
}  
#endif