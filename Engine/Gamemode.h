#pragma once

#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "PokerGameplay.h"
#include "FiveCardDraw.h"
#include "BlackjackEngine.h"
#include "CLI.h"
#include "Read_UserData.h"

void StandardPoker() {
    CLI::clearScreen();

    // Initialize players
    std::cout << "How many players do you want to play with?"
                << std::endl;
    int playerCount = CLI::getOptionNum(2, 8);

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

    drawSinglePokerGameRound(player, playerOrder, 5);
}

void FiveCardDrawGame() {
    CLI::clearScreen();

    // Initialize players
    std::cout << "How many players do you want to play with?" << std::endl;
    int playerCount = CLI::getOptionNum(2, 8);

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
    std::cout << "How many players do you want to play with?" << std::endl;
    int playerCount = CLI::getOptionNum(2, 8);

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

    drawMultiplePokerGameRound(player, playerOrder, 5);
}

void BlackjackGame() {

}

void ExitGame(bool &exited) {
    std::cout << "Thank you for playing our games!";
    exited = true;
}

void GameMode(bool &exited) {
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