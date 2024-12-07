#ifndef __CLI__
#define __CLI__

#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include "Read_UserData.h"
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
        std::cout << std::setfill('=') << std::setw(60) << "=" << std::endl;
        std::cout << std::setfill(' ') << std::setw(40) << "TUTORIAL MODE GAMEPLAY" << std::endl;
        std::cout << std::setfill('=') << std::setw(60) << "=" << std::endl;

        // Display the note section
        std::cout << "\nNOTE:\n";
        std::cout << "In order to have a full experience, users must have knowledge of:\n"
            << "   - Poker Hands: Full House, Flush, One Pair, etc.\n"
            << "   - Advanced Actions: CALL, RAISE, ALL IN.\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;

        std::cout << "\n1. Standard Poker:\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << "   Each player is dealt 5 cards (visible to others).\n"
            << "   Players proceed to a betting round, choosing actions like\n"
            << "   CHECK, CALL, RAISE, FOLD, or ALL IN.\n"
            << "   At the showdown, the pot is distributed based on hand rankings.\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;

        std::cout << "\n2. Five Card Draw Poker:\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << "   Players are dealt 5 cards and may choose cards to replace.\n"
            << "   After drawing, a betting round takes place.\n"
            << "   At the showdown, the pot is distributed based on hand rankings.\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;

        std::cout << "\n3. Five Card Stud Poker:\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << "   Initial Deal: 1 face-down card and 1 face-up card.\n"
            << "   Betting begins with the lowest face-up card (bring-in).\n"
            << "   Players receive 1 additional face-up card each round (5 rounds total).\n"
            << "   Final round involves a showdown if 2+ players remain.\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;

        std::cout << "\n4. Chinese Poker Game:\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << "   Cards are valued: Number (face value), Face (10), Ace (1/10/11).\n"
            << "   Players are dealt 2 cards and may draw up to 3 more.\n"
            << "   Winner is closest to 21 points. Special hands:\n"
            << "      - QUAC: Hand >21 or <16 (automatic loss unless all lose).\n"
            << "      - XI DACH: Ace + 10-value card = 21.\n"
            << "      - XI BAN: Pair of Aces.\n"
            << "      - NGU LINH: 5 cards, total <21.\n";
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << "Press Enter to go back...";
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }

    /// @brief This function will ask the player choose a main option
    /// @return An integer shows the player's choice
    inline int getMainOption() {
        std::cout << "Main menu:\n\n";
        std::cout << "1. New game\n";
        std::cout << "2. Tutorial\n";
       // std::cout << "3. learder board\n";
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
        std::cout << "4. Chinese Poker\n\n";
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