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
}
