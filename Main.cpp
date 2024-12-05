#include "Engine/Gamemode.h"

int main() {
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

    User_Action User;
    User.Choice();
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
