#include "Engine/Gamemode.h"

int main() {
    // Clear the Screen
    CLI::clearScreen();
    
    // Log in - Sign Up 
    User_Action User;
    User.Choice();

    // Get in the game
    bool exited = 0;
    while (!exited) {
        CLI::clearScreen();
        CLI::title();

        int userChoice = CLI::getMainOption();

        if (userChoice == 0) {
            ExitGame(exited);
        } else if (userChoice == 1) {
            CLI::clearScreen();
            GameMode(exited);
        } else if (userChoice == 2) {
            CLI::clearScreen();
            CLI::printTutorial();
        }
    }


    return 0;
    // Hand hand;
    // hand.add(Rank::ACE << 2 | Suit::CLUBS);
    // hand.add(Rank::FIVE << 2 | Suit::CLUBS);
    // hand.add(Rank::FIVE << 2 | Suit::CLUBS);
    // auto eval = XiDachEngine::evalXiDach(hand);
    // if(eval.first == XiDachHandType::NGU_LINH) std::cout << " yeah" << std::endl;
    // else std::cout << "dmm" << std::endl;
    // std::cout << eval.second << std::endl;
}
