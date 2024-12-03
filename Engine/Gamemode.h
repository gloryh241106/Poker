#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "FiveCardStud.h"
#include "PokerEngine.h"
#include "BlackjackEngine.h"
#include "CLI.h"

void GameMode(bool &running) {
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
            ExitGame(running);
            break;
        default:
            CLI::clearScreen();
    }
}

void StandardPoker() {
    CLI::clearScreen();

    // Initialize players
    std::cout << "How many players do you want to play with?"
                << std::endl;
    int playerCount = CLI::getOptionNum(2, 8);

    std::vector<Player> player(playerCount, Player {Hand(), Random::_name(), 1000, 0, 0, 0, 0});

    // Masking card
    for (int i = 0; i < playerCount; i++) {
        player[i].hand.setMask(0x01);
    }
}

void FiveCardDrawGame() {

}

void FiveCardStudGame() {
    CLI::clearScreen();

    // Initialize players
    std::cout << "How many players do you want to play with?"
                << std::endl;
    int playerCount = CLI::getOptionNum(2, 8);

    std::vector<Player> player(
        playerCount, Player {Hand(), Random::_name(), 1000, 0, 0, 0, 0});

    // Masking card
    for (int i = 0; i < playerCount; i++) {
        player[i].hand.setMask(0x01);
    }

    // Initialize player's order
    std::deque<int> playerOrder;
    for (int i = 0; i < playerCount; i++) {
        playerOrder.push_back(i);
    }
    drawPokerGameRound(player, playerOrder, 5);

    // Uncomment this to play multiple rounds---------------------------
    
    // int round = 1;
    // while (player.size() > 1) {
    //     std::cout << "\n\n"; // CLI::clearScreen();
    //     std::cout << "Round " << round << std::endl;
    //     CLI::sleep(1000);
    //     gameRound(player, playerOrder, 5);
    //     round++;
    // }
    
    //------------------------------------------------------------------
}

void BlackjackGame() {

}

void ExitGame(bool &running) {
    running = false;
}
#endif