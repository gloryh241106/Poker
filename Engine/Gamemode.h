#pragma once

#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "ChineseBlackjackGameplay.h"
#include "CLI.h"
#include "FiveCardDraw.h"
#include "Player.h"
#include "PokerGameplay.h"
#include "Read_UserData.h"

void StandardPoker(std::string Username) {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    player[0].hand = Hand();
    player[0].name = Username;
    player[0].chips = User_Money_Data[Username];
    player[0].bet = 0;
    player[0].folded = 0;
    player[0].lost = 0;
    player[0].allIn = 0;

    for (size_t i = 1; i < player.size(); ++i) {
        player[i].hand = Hand();
        player[i].name = Random::_name();
        player[i].chips = 1000;
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].lost = 0;
        player[i].allIn = 0;
    }


    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    int round = 1;
    while (playerOrder.size() > 1) {
        std::cout << "Round " << round << std::endl;
        standardPokerGameRound(player, playerOrder, 5);
        round++;
        std::cout << "Do you want to play another round? ";
        if (!CLI::getOptionYN()) break;
    }
}

void FiveCardDrawGame(std::string Username) {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();


    std::vector<Player> player(playerCount, Player());
    player[0].hand = Hand();
    player[0].name = Username;
    player[0].chips = User_Money_Data[Username];
    player[0].bet = 0;
    player[0].folded = 0;
    player[0].lost = 0;
    player[0].allIn = 0;

    for (size_t i = 1; i < player.size(); ++i) {
        player[i].hand = Hand();
        player[i].name = Random::_name();
        player[i].chips = 1000;
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].lost = 0;
        player[i].allIn = 0;
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    // Initialize deck
    Deck deck;

    int pot = 0;
    // int dealerIndex = 0;

    int round = 1;
    while (playerOrder.size() > 1) {
        std::cout << "Round " << round << std::endl;
        Phase1(player, playerOrder, deck);
        Phase2(player, playerOrder, pot);
        round++;
        std::cout << "Do you want to play another round? ";
        if (!CLI::getOptionYN()) break;
    }
}

void FiveCardStudGame(std::string Username) {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    player[0].hand = Hand();
    player[0].name = Username;
    player[0].chips = User_Money_Data[Username];
    player[0].bet = 0;
    player[0].folded = 0;
    player[0].lost = 0;
    player[0].allIn = 0;

    for (size_t i = 1; i < player.size(); ++i) {
        player[i].hand = Hand();
        player[i].name = Random::_name();
        player[i].chips = 1000;
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].lost = 0;
        player[i].allIn = 0;
    }

    // Masking card
    for (int i = 0; i < playerCount; i++) {
        player[i].hand.setMask(0x01);
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    int round = 1;
    while (playerOrder.size() > 1) {
        std::cout << "Round " << round << std::endl;
        fiveCardStudPokerGameRound(player, playerOrder, 5);
        round++;
        std::cout << "Do you want to play another round? ";
        if (!CLI::getOptionYN()) break;
    }
}

void ChinesePokerGame(std::string Username) {

    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    player[0].hand = Hand();
    player[0].name = Username;
    player[0].chips = User_Money_Data[Username];
    player[0].bet = 0;
    player[0].folded = 0;
    player[0].lost = 0;
    player[0].allIn = 0;

    for (size_t i = 1; i < player.size(); ++i) {
        player[i].hand = Hand();
        player[i].name = Random::_name();
        player[i].chips = 1000;
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].lost = 0;
        player[i].allIn = 0;
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    int round = 1;
    while (playerOrder.size() > 1) {
        std::cout << "Round " << round << std::endl;
        ChineseBlackjackGameRound(player, playerOrder);
        round++;
        std::cout << "Do you want to play another round? ";
        if (!CLI::getOptionYN()) break;
    }
}

void ExitGame(bool& exited) {
    std::cout << "Thank you for playing our games!";
    exited = true;
}

void GameMode(bool& exited, std::string Username) {
    int userChoice = CLI::getGameMode();
    switch (userChoice) {
    case 1:
        StandardPoker(Username);
        break;
    case 2:
        FiveCardDrawGame(Username);
        break;
    case 3:
        FiveCardStudGame(Username);
        break;
    case 4:
        ChinesePokerGame(Username);
        break;
    case 0:
        ExitGame(exited);
        break;
    default:
        CLI::clearScreen();
    }
}
#endif