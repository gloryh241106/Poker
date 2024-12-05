#ifndef __CLI__
#define __CLI__

#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

namespace CLI {
    void clearScreen() {
        system("cls");
    }

    void sleep(int milliseconds) {
        // https://stackoverflow.com/a/10613664
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    // Ask user fo a number in range [n,m]
    int getOptionNum(int n, int m) {
        int userChoice = -1;
        while (userChoice < n || userChoice > m) {
            if (n != m)
                std::cout << "(" << n << " - " << m << "): ";
            else
                std::cout << "(" << n << "): ";
            std::cin >> userChoice;
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

        return userChoice;
    }

    bool getOptionYN() {
        std::string userChoiceStr;
        while (1) {
            std::cout << "(y/n): ";
            std::getline(std::cin, userChoiceStr);
            if (userChoiceStr == "y" || userChoiceStr == "Y") return 1;
            if (userChoiceStr == "n" || userChoiceStr == "N") return 0;
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
        std::cout << "Here goes tutorial\n\n";
        std::cout << "Press Enter to go back...";
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }

    int getMainOption() {
        std::cout << "Main menu:\n\n";
        std::cout << "1. New game\n";
        std::cout << "2. Tutorial\n";
        std::cout << "0. Exit\n\n";
        std::cout << "Choose an option by pressing a number ";

        return getOptionNum(0, 2);
    }

    int getGameMode() {
        std::cout << "Choose a Gamemode:\n\n";
        std::cout << "1. Standard Poker\n";
        std::cout << "2. Five Card Draw Poker\n";
        std::cout << "3. Five Card Stud Poker\n";
        std::cout << "4. Blackjack\n\n";
        std::cout << "Choose an option by pressing a number: ";

        return getOptionNum(1, 4);
    }

    int getPlayerNum() {
        std::cout << "Number of players: ";

        return getOptionNum(2, 8);
    }
}  // namespace CLI

#endif