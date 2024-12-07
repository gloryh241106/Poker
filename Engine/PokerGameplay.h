#pragma once

#include <chrono>
#include <deque>
#include <iostream>
#include <thread>
#include <vector>
#include "Read_UserData.h"
#include "CLI.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include "PokerEngine.h"
#include "Random.h"
#include "deque_helper.h"

enum class PlayerAction { NONE, CHECK, CALL, BET, RAISE, FOLD, ALL_IN };

/// @brief Ask player action
/// @param player Struct Player 
/// @param currBet The current bet
/// @param minRaiseDiff The min raise difference
/// @param preflop Boolean is preflop round
/// @return enum PlayerAction
PlayerAction askPlayerAction(Player& player, const int& currBet, const int& minRaiseDiff, bool& preflop) {
    if (currBet == 0) {
        std::cout << "1. Check" << std::endl;
        std::cout << "2. Raise" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);

        if (op == 1) {
            return PlayerAction::CHECK;
        }
        else if (op == 2) {
            preflop = false;
            return PlayerAction::RAISE;
        }
        else {
            return PlayerAction::FOLD;
        }
    }
    else if (currBet >= player.chips) {
        std::cout << "1. All In" << std::endl;
        std::cout << "2. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 2);

        if (op == 1) {
            return PlayerAction::ALL_IN;
        }
        else {
            return PlayerAction::FOLD;
        }
    }
    else if (currBet + minRaiseDiff >= player.chips) {
        std::cout << "1. Call" << std::endl;
        std::cout << "2. All In" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);

        if (op == 1) {
            return PlayerAction::CALL;
        }
        else if (op == 2) {
            return PlayerAction::ALL_IN;
        }
        else {
            return PlayerAction::FOLD;
        }
    }
    else {
        std::cout << "1. Call" << std::endl;
        std::cout << "2. Raise" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);

        if (op == 1) {
            return PlayerAction::CALL;
        }
        else if (op == 2) {
            return PlayerAction::RAISE;
        }
        else {
            return PlayerAction::FOLD;
        }
    }

    return PlayerAction::NONE;
}

/// @brief https://e...content-available-to-author-only...a.org/wiki/Betting_in_poker
/// @return Returns the index of the player who won the round, otherwise returns -1
int studPokerBetRound(std::vector<Player>& players, std::deque<int>& playerOrder, int blind, bool preflop, int& pot, bool isFiveCardStud) {
    int playerCount = players.size();
    int playerInGame = playerOrder.size();

    if (playerInGame < 1) {
        return -1;
    }

    // Check if there is only one player left
    if (playerInGame == 1) {
        return playerOrder.front();
    }

    // Forced bets
    bool forcedBet = 0;
    if (preflop) {
        forcedBet = 1;
        if (playerInGame == 2) {
            players[playerOrder.front()].bet += blind;  // Small blind
            dequeNext(playerOrder);
            players[playerOrder.front()].bet += blind * 2;  // Big blind
        }
        else {
            dequeNext(playerOrder);
            players[playerOrder.front()].bet += blind;  // Small blind
            dequeNext(playerOrder);
            players[playerOrder.front()].bet += blind * 2;  // Big blind
        }
    }

    int currBet = preflop ? blind * 2 : 0;

    int minRaiseDiff = preflop ? blind * 2 : 0;

    // If preflop, the player after the big blind is the first to act
    // Else, the dealer is the first to act
    int raisedPlayer = playerOrder.front();

    bool live = 1;  // The betting round is live
    while (live) {
        live = false;
        do {
            dequeNext(playerOrder);

            // Skip players who have folded
            if (players[playerOrder.front()].folded) {
                dequeNext(playerOrder);
                continue;
            }

            // If the GameMode is Five Card Stud, print all players' hand
            if (isFiveCardStud) {
                CLI::clearScreen();
                for (int i : playerOrder) {
                    std::cout << "Player's " <<players[playerOrder[i]].name
                        << " hand: " << players[i].hand.toString(1)
                        << std::endl;
                }
            }

            CLI::sleep(1000);
            // Print the player hand for betting
            std::cout << "\n\n";
            std::cout << "Player " << players[playerOrder.front()].name
                << "'s turn " << std::endl;
            std::cout << "Your hand: "
                << players[playerOrder.front()].hand.toString() << std::endl;
            std::cout << "Your remaining chips: "
                << players[playerOrder.front()].chips << std::endl;
            std::cout << "You bet: "
                << players[playerOrder.front()].bet << std::endl;

            std::cout << "Pot: " << pot << std::endl;

            if (players[playerOrder.front()].allIn) {
                std::cout << "You have gone all in" << std::endl;
                CLI::getEnter();
                if (playerOrder.front() == raisedPlayer) {
                    break;
                }
                else {
                    // dequeNext(playerOrder);
                    continue;
                }
            }

            std::cout << "Current bet amount: " << currBet << std::endl;
            std::cout << "What do you want to do?" << std::endl;

            PlayerAction op = askPlayerAction(players[playerOrder.front()], currBet, minRaiseDiff, preflop);
            std::cout << std::endl;

            if (op == PlayerAction::CHECK ||
                op == PlayerAction::CALL) {  // CHECK/CALL
                players[playerOrder.front()].bet = currBet;

                if (players[playerOrder.front()].chips <= currBet) {  // ALL IN
                    players[playerOrder.front()].allIn = 1;
                    players[playerOrder.front()].bet = players[playerOrder.front()].chips;
                }

                // if (playerOrder.front() == raisedPlayer) {
                //     break;
                // } else {
                //     dequeNext(playerOrder);
                //     continue;
                // }
            }
            else if (op == PlayerAction::BET) {
                std::cout << "How much do you want to bet?" << std::endl;
                int bet = CLI::getOptionNum(blind * 2, players[playerOrder.front()].chips);
                minRaiseDiff = bet - currBet;
                currBet = bet;
                players[playerOrder.front()].bet = currBet;

                if (currBet == players[playerOrder.front()].chips) {  // ALL IN
                    players[playerOrder.front()].allIn = 1;
                }

                live = true;
                raisedPlayer = playerOrder.front();
            }
            else if (op == PlayerAction::RAISE) {
                std::cout << "Min raise: " << currBet + minRaiseDiff
                    << std::endl;
                std::cout << "How much do you want to raise to?" << std::endl;
                int raise = CLI::getOptionNum(currBet + minRaiseDiff, players[playerOrder.front()].chips);
                minRaiseDiff = raise - currBet;
                currBet = raise;
                players[playerOrder.front()].bet = currBet;

                if (currBet >= players[playerOrder.front()].chips) {  // ALL IN
                    players[playerOrder.front()].allIn = 1;
                }

                live = true;
                raisedPlayer = playerOrder.front();
            }
            else if (op == PlayerAction::ALL_IN) {  // ALL IN
                players[playerOrder.front()].allIn = 1;
                players[playerOrder.front()].bet = players[playerOrder.front()].chips;
                int diff = players[playerOrder.front()].chips - currBet;
                currBet = std::max(currBet, players[playerOrder.front()].bet);

                // If the player goes all-in, others are only allowed to
                // re-raise if he exceeds the minimum raise.
                if (diff > minRaiseDiff) {
                    minRaiseDiff = diff;
                    live = true;
                    raisedPlayer = playerOrder.front();
                }
            }
            else if (op == PlayerAction::FOLD) {  // FOLD
                players[playerOrder.front()].folded = 1;
                playerInGame--;
            }

            // Check if there is only one player left
            if (playerInGame == 1) {
                for (int i = 0; i < playerCount; i++) {
                    if (!players[i].folded) {
                        return i;
                    }
                }
            }

            // Clear screen for next player
            CLI::clearScreen();

            // dequeNext(playerOrder);
        } while (playerOrder.front() != raisedPlayer);
    }

    // Collect the pot
    for (int i : playerOrder) {
        pot += players[i].bet;
        players[i].showdownBet += players[i].bet;
        players[i].chips -= players[i].bet;
        players[i].bet = 0;
    }

    return -1;
}

/// @brief This function will showdown all the result, including player's hand, chips, remaining
/// @param player Vector contains N players
/// @param playerOrder Deque contains player order
/// @param pot Pot of the game
void showdown(std::vector<Player>& players, std::deque<int>& playerOrder, int& pot) {
    // int pot = 0;
    int playerCount = playerOrder.size();
    for (int i : playerOrder) {
        // std::cout << "Here " << p.bet << std::endl;
        // CLI::getEnter();
        // pot += p.bet;
        // p.chips -= p.bet;
        if (players[i].folded) continue;
        PokerEngine::eval(players[i].hand.bit());
    }

    std::vector<int> playerRank(playerOrder.begin(), playerOrder.end());

    // Sort the players by hand strength
    std::sort(playerRank.begin(), playerRank.end(), [&](int a, int b) {
        return PokerEngine::compareHands(players[a].hand, players[b].hand);
        });

    // Display the hands
    CLI::clearScreen();
    std::cout << "Showdown" << std::endl;
    for (int i = 0; i < playerCount; i++) {
        if (players[playerRank[i]].folded) continue;
        std::cout << "Player " << players[playerRank[i]].name << " "
            << "'s hand: " << players[playerRank[i]].hand.toString()
            << " (" << PokerEngine::type(players[playerRank[i]].hand)
            << ")" << std::endl;
    }



    std::cout << std::endl;
    std::vector<int> temp;
    for (int i = 0; i < playerCount; i++)
        temp.push_back(User_Game_Won[players[i].name]);
    // Distribute the pot
    int i = 0;
    while (i < playerCount && pot > 0) {
        players[playerRank[i]].showdownBet = std::min(pot, players[playerRank[i]].showdownBet * (playerCount - i));
        long long MoneyUserTemp = players[playerRank[i]].chips;
        players[playerRank[i]].chips += players[playerRank[i]].showdownBet;

        //Check if player chips after pot distributed increase or not. If increase means player won the game, else they lost.
        if (players[playerRank[i]].chips >= MoneyUserTemp) //Mean that after a game. User money has increased
            User_Game_Won[players[playerRank[i]].name]++;  //  increase user number of win game
        User_Money_Data[players[playerRank[i]].name] = players[playerRank[i]].chips; // Update and save user money
        User_Game_Played[players[playerRank[i]].name]++; // Update and save User Game Played (in order to calculate User Win Rate)
        pot -= std::min(pot, players[playerRank[i]].showdownBet * (playerCount - i));
        i++;
    }

    // Display the chips
    for (int j = 0; j < playerCount; j++) {
        if (User_Game_Won[players[j].name] > temp[j]) {

            std::cout << "Player " << players[j].name << " has won " << std::endl;
            std::cout << "Player " << players[j].name << " has " << " " << players[j].chips << " " << "chips currently" << std::endl;
        }
        else {
            std::cout << "Player " << players[j].name << " has lost " << std::endl;
            std::cout << "Player " << players[j].name << " has " << " " << players[j].chips << " " << "chips currently" << std::endl;
        }
        //User_Action User;
        //User.Display_Leader_Board(players[j].name);
    }


    // Remove lost players
    i = 0;
    while (i < playerOrder.size()) {
        if (players[playerOrder.front()].chips == 0) {
            players[playerOrder.front()].lost = 1;
            playerOrder.pop_front();
            continue;
        }

        dequeNext(playerOrder);
        i++;
    }

    // Reset the players
    for (int k : playerOrder) {
        players[k].hand.clear();
        players[k].bet = 0;
        players[k].folded = 0;
        players[k].allIn = 0;
        players[k].showdownBet = 0;
    }

    CLI::getEnter();
}

/// @brief This function will tell the last player playing the game, and all pot is belongs to that player
/// @param player Vector contains N players
/// @param playerOrder Deque contains player order
/// @param lastPlayer Index of the player
/// @param pot Total money bet from the game
void lastPlayerStanding(std::vector<Player>& player, std::deque<int>& playerOrder, int lastPlayer, int& pot) {
    CLI::clearScreen();
    std::cout << "Player " << player[lastPlayer].name << " wins the round" << std::endl;
    player[lastPlayer].chips += pot;
    CLI::getEnter();

    // Reset the players
    for (int i : playerOrder) {
        player[i].hand.clear();
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].allIn = 0;
        player[i].showdownBet = 0;
    }
}

/// @brief This function will draw the Five Card Stud game
void fiveCardStudPokerGameRound(std::vector<Player>& player, std::deque<int>& playerOrder, int blind) {
    int playerCount = playerOrder.size();

    // Initialize deck
    Deck deck;

    int pot = 0;
    // int dealerIndex = 0;

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Pre-flop ----------------------------------------------------------------
    CLI::clearScreen();
    std::cout << "Pre-flop" << std::endl;
    CLI::sleep(1000);
    int lastPlayer = studPokerBetRound(player, playerOrder, blind, 1, pot, 1);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Flop --------------------------------------------------------------------
    CLI::clearScreen();
    std::cout << "Flop" << std::endl;
    CLI::sleep(1000);
    lastPlayer = studPokerBetRound(player, playerOrder, blind, 0, pot, 1);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Turn --------------------------------------------------------------------
    CLI::clearScreen();
    std::cout << "Turn" << std::endl;
    CLI::sleep(1000);
    lastPlayer = studPokerBetRound(player, playerOrder, blind, 0, pot, 1);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // River -------------------------------------------------------------------
    CLI::clearScreen();
    std::cout << "River" << std::endl;
    CLI::sleep(1000);
    lastPlayer = studPokerBetRound(player, playerOrder, blind, 0, pot, 1);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Showdown
    std::cout << "Calculating card...";
    CLI::sleep(4000);
    showdown(player, playerOrder, pot);

    // After playing game, clear the screen for returning the main menu
    CLI::clearScreen();
}

/// @brief This function will draw the Standard Poker Game
void standardPokerGameRound(std::vector<Player>& player, std::deque<int>& playerOrder, int blind) {
    int playerCount = playerOrder.size();

    // Initialize deck
    Deck deck;

    int pot = 0;

    // Deal cards
    std::cout << "Dealing card..." << std::endl;
    CLI::sleep(1000);
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < 5; j++) {
            player[playerOrder.front()].hand.add(deck.draw());
        }

        dequeNext(playerOrder);
    }

    // Bet
    CLI::clearScreen();
    std::cout << "Betting" << std::endl;
    CLI::sleep(1000);
    int lastPlayer = studPokerBetRound(player, playerOrder, blind, 0, pot, 0);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }

    // Showdown
    showdown(player, playerOrder, pot);

    // After playing game, clear the screen for returning the main menu
    CLI::clearScreen();
}