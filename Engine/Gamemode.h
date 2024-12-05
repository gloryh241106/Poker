#pragma once

#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "BlackjackGameplay.h"
#include "CLI.h"
#include "FiveCardDraw.h"
#include "Player.h"
#include "PokerGameplay.h"
#include "Read_UserData.h"

void StandardPoker() {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    for (Player& p : player) {
        p.hand = Hand();
        p.name = Random::_name();
        p.chips = 1000;
        p.bet = 0;
        p.folded = 0;
        p.lost = 0;
        p.allIn = 0;
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    standardPokerGameRound(player, playerOrder, 5);
}

void FiveCardDrawGame() {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    for (Player& p : player) {
        p.hand = Hand();
        p.name = Random::_name();
        p.chips = 1000;
        p.bet = 0;
        p.folded = 0;
        p.lost = 0;
        p.allIn = 0;
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

    Phase1(player, playerOrder, deck);
    Phase2(player, playerOrder, pot);
}

void FiveCardStudGame() {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    for (Player& p : player) {
        p.hand = Hand();
        p.name = Random::_name();
        p.chips = 1000;
        p.bet = 0;
        p.folded = 0;
        p.lost = 0;
        p.allIn = 0;
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
    }
}

void BlackjackGame() {
    CLI::clearScreen();

    // Initialize players
    int playerCount = CLI::getPlayerCount();

    std::vector<Player> player(playerCount, Player());
    for (Player& p : player) {
        p.hand = Hand();
        p.name = Random::_name();
        p.chips = 1000;
        p.bet = 0;
        p.folded = 0;
        p.lost = 0;
        p.allIn = 0;
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }

    int round = 1;
    while (playerOrder.size() > 1) {
        std::cout << "Round " << round << std::endl;
        xiDachGameRound(player, playerOrder);
    }
}

void ExitGame(bool& exited) {
    std::cout << "Thank you for playing our games!";
    exited = true;
}

void GameMode(bool& exited) {
    int userChoice = CLI::getGameMode();
    switch (userChoice) {
        case 1:
            StandardPoker();
            break;
        case 2:
            FiveCardDrawGame();
            break;
        case 3:
            FiveCardStudGame();
            break;
        case 4:
            BlackjackGame();
            break;
        case 0:
            ExitGame(exited);
            break;
        default:
            CLI::clearScreen();
    }
}
#endif