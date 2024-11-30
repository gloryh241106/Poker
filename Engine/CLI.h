#ifndef __CLI__
#define __CLI__

#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

namespace CLI {
void clearScreen() { std::cout << "\x1b[2J\x1b[H"; }

void sleep(int milliseconds) {
    // https://stackoverflow.com/a/10613664
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Ask user fo a number in range [n,m]
int getOptionNum(int n, int m) {
    int op = -1;
    while (op < n || op > m) {
        std::cout << "(" << n << " - " << m << "): ";
        std::cin >> op;
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
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
    return 0;
}

void getEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
}

void title() {
    std::cout << "\n";
    std::cout << "  ____ _               _                    _             \n";
    std::cout << " / ___| | __ _ ___ ___(_) ___   _ __   ___ | | _____ _ __ \n";
    std::cout << "| |   | |/ _` / __/ __| |/ __| | '_ \\ / _ \\| |/ / _ \\ "
                 "'__|\n";
    std::cout << "| |___| | (_| \\__ \\__ \\ | (__  | |_) | (_) |   <  __/ "
                 "|   \n";
    std::cout << " \\____|_|\\__,_|___/___/_|\\___| | .__/ "
                 "\\___/|_|\\_\\___|_|   \n";
    std::cout << "                               |_|                        \n";
    std::cout << "\n";
}

void printTutorial() {
    std::cout << "Here goes tutorial\n";
    std::cout << "Press Enter to go back...";
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
}

int getMainOption() {
    std::cout << "Main menu:\n\n";
    std::cout << "1.New game\n";
    std::cout << "2.Tutorial\n";
    std::cout << "3.Leaderboard\n";
    std::cout << "0.Exit\n\n";
    return getOptionNum(0, 3);
}

int getPlayerMode() {
    std::cout << "Play against:\n";
    std::cout << "1.Humans (PVP)\n";
    std::cout << "2.Bots (PVE)\n";
    return getOptionNum(1, 2);
}

int getGameMode() {
    std::cout << "Gamemode:\n";
    std::cout << "1.POKER\n";
    return getOptionNum(1, 1);
}

int getPlayerNum() {
    std::cout << "Number of players ";
    return getOptionNum(2, 8);
}
}  // namespace CLI

#endif