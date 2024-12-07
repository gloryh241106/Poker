#include "Engine/Gamemode.h"

int main() {
    // Clear the Screen
    CLI::clearScreen();
    std::string Username;
    bool flag;
    // Log in - Sign Up 
    User_Action User;
    User.Load_Data();
    User.Load_Money();
    User.Load_Data_NumGame();
    //User.Load_LeaderBoard();
    flag = User.Choice(Username);
    std::string Username1 = Username;
    
    if (!flag) return 0;
    
    else {
        // Get in the game
        bool exited = 0;
        while (!exited) {
            CLI::clearScreen();
            CLI::title();

            int userChoice = CLI::getMainOption();

            if (userChoice == 0) {
                ExitGame(exited);
            }
            else if (userChoice == 1) {
                CLI::clearScreen();
                GameMode(exited, Username1);
            }
            else if (userChoice == 2) {
                CLI::clearScreen();
                CLI::printTutorial();
            }
            //else if (userChoice == 3) {
             //  CLI::clearScreen();
             //  User.Leader_Board();
            //}
        }
    }
    User.MoneyGameToFile();
    //User.WinRateToFile();

    return 0;
}
