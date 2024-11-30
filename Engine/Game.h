#ifndef __GAME__
#define __GAME__

#include <iomanip>
#include <string>

#include "Hand.h"
#include "PokerEngine.h"
#include "Random.h"
#include "XiDachEngine.h"

enum PlayerAction {
    FOLD,
    CALL,
    RAISE,
    ALL_IN,
};

enum GameMode {
    POKER = 0,
    STUDPOKER = 1,
    XIDACH = 2,
};

enum PlayerMode {
    PVP = 0,
    PVE = 1,
};

class Game {
   public:
    static const int MAX_PLAYER = 8;
    bool exit = 0;
    PlayerMode playerMode;
    GameMode gameMode;
    int playerNum;
    Deck deck;
    int ante = 10;
    int playerOffset;
    // std::vector<Player> players;
    Game() { playerOffset = intRNG() % MAX_PLAYER; }

    void printClearScreen() { std::cout << "\x1b[2J\x1b[H"; }

    // Ask user fo a number in range [0,n]
    int getOptionNum(int n) {
        int op = -1;
        while (op < 0 || op > n) {
            std::cout << "(0-" << n << "): ";
            std::cin >> op;
            std::cin.ignore(1000, '\n');
        }
        return op;
    }

    // Ask user fo a number in range [n,m]
    int getOptionNum(int n, int m) {
        int op = -1;
        while (op < n || op > m) {
            std::cout << "(" << n << "-" << m << "): ";
            std::cin >> op;
            std::cin.ignore(1000, '\n');
        }
        return op;
    }

    bool getOptionYN() {
        std::string opStr;
        while (1) {
            std::cout << "(y/n): ";
            std::getline(std::cin, opStr);
            if (opStr == "y" || opStr == "Y") return 1;
            if (opStr == "n" || opStr == "N") return 0;
        }
    }

    void printTitle() {
        std::cout << "\n";
        std::cout
            << "  ____ _               _                    _             \n";
        std::cout
            << " / ___| | __ _ ___ ___(_) ___   _ __   ___ | | _____ _ __ \n";
        std::cout << "| |   | |/ _` / __/ __| |/ __| | '_ \\ / _ \\| |/ / _ \\ "
                     "'__|\n";
        std::cout << "| |___| | (_| \\__ \\__ \\ | (__  | |_) | (_) |   <  __/ "
                     "|   \n";
        std::cout << " \\____|_|\\__,_|___/___/_|\\___| | .__/ "
                     "\\___/|_|\\_\\___|_|   \n";
        std::cout
            << "                               |_|                        \n";
        std::cout << "\n";
    }

    void printTutorial() {
        std::cout << "Here goes tutorial\n";
        std::cout << "Press Enter to go back...";
        std::cin.ignore(1000, '\n');
    }

    int getMainOption() {
        std::cout << "Main menu:\n\n";
        std::cout << "1.New game\n";
        std::cout << "2.Tutorial\n";
        std::cout << "3.Leaderboard\n";
        std::cout << "0.Exit\n\n";
        return getOptionNum(3);
    }

    int getPlayerMode() {
        std::cout << "Play against:\n";
        std::cout << "0.Humans (PVP)\n";
        std::cout << "1.Bots (PVE)\n";
        return getOptionNum(1);
    }

    int getGameMode() {
        std::cout << "Gamemode:\n";
        std::cout << "0.POKER\n";
        std::cout << "1.STUD POKER\n";
        std::cout << "2.XI DACH\n";
        return getOptionNum(2);
    }

    int getPlayerNum() {
        std::cout << "Number of players ";
        return getOptionNum(2, 8);
    }

    std::string getPVEName() {
        std::cout << "Your name: ";
        std::string name;
        std::getline(std::cin, name);
        return name;
    }

    void getPVPNames();  // TODO

    void getGameInfo() {
        playerMode = (PlayerMode)getPlayerMode();
        playerNum = getPlayerNum();
        gameMode = (GameMode)getGameMode();
    }

    // void getPlayerInfo() {
    //     if (playerMode == PlayerMode::PVE) {
    //         players[0].name = getPVEName();
    //     }
    // }
};

#endif