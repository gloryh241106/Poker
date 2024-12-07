#ifndef __CLI__
#define __CLI__

#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

namespace CLI {
    /// @brief This function will clear all the screen
    inline void clearScreen() {
        system("cls");
    }

    /// @brief This function will let the program sleep in miliseconds
    /// @param milliseconds 
    inline void sleep(int milliseconds) {
        // https://stackoverflow.com/a/10613664
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    /// @brief This function will ask user choose a number in range [n,m]
    /// @param n The left side
    /// @param m The right side
    /// @return An integer shows the player's option
    inline int getOptionNum(int n, int m) {
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

    /// @brief This function will get the user's choice (Which is a number in range [n, m])
    /// @param n The left side
    /// @param m The right side
    /// @return An integer
    inline int getOneNumber(int n, int m) {
        int userChoice = -1;
        while (userChoice < n || userChoice > m) {
            std::cin >> userChoice;
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            if (userChoice < n || userChoice > m) 
                std::cout << "Invalid value! Please enter again! \n";
        }

        return userChoice;
    }

    /// @brief This function will ask user choose Yes or No 
    /// @return Boolean shows the player's option
    inline bool getOptionYN() {
        std::string userChoiceStr;
        do {
            std::cout << "(y/n): ";
            std::getline(std::cin, userChoiceStr);
            if (userChoiceStr == "y" || userChoiceStr == "Y") return 1;
            else if (userChoiceStr == "n" || userChoiceStr == "N") return 0;
            else {
                std::cout << "Invalid choice! Please enter again! \n";
            }
        } while (1);

        return 0;
    }

    /// @brief This function will get the player's Enter
    inline void getEnter() {
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }

    /// @brief This function will print the game title
    inline void title() {
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

    /// @brief This function will print the game tutorial
    inline void printTutorial() {
        std::cout << "Here goes tutorial\n\n";
        std::cout << "Press Enter to go back...";
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }

    /// @brief This function will ask the player choose a main option
    /// @return An integer shows the player's choice
    inline int getMainOption() {
        std::cout << "Main menu:\n\n";
        std::cout << "1. New game\n";
        std::cout << "0. Exit\n\n";
        std::cout << "Choose an option by pressing a number ";

        return getOptionNum(0, 2);
    }

    /// @brief This function will ask the player choose a game mode
    /// @return An integer shows the player's choice
    inline int getGameMode() {
        std::cout << "Choose a Gamemode:\n\n";
        std::cout << "1. Standard Poker\n";
        std::cout << "2. Five Card Draw Poker\n";
        std::cout << "3. Five Card Stud Poker\n";
        std::cout << "4. Chinese Blackjack\n\n";
        std::cout << "Choose an option by pressing a number: ";

        return getOptionNum(1, 4);
    }

    /// @brief This function will ask the player choose a number of people to play with
    /// @return An integer shows the player's choice
    inline int getPlayerCount() {
        std::cout << "How many players do you want to play with?" << std::endl;
        return getOptionNum(2, 8);
    }
}  // namespace CLI

#endif