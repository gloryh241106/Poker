#ifndef __GAMEBUTTON__
#define __GAMEBUTTON__

#include "RenderWindow.h"
#include "Button.h"

void onImageClick() {
    std::cout << "Image clicked" << '\n';
}

// Start Screen
void InitGame(RenderWindow window, bool &gameRunning, SDL_Event event) {
    // Render and display image, entities
    SDL_Texture* gameInit = window.loadTexture("Assets/Screen/Game_Init.png");
    Button startGame = {window.getRenderer(), "Assets/Button/Button_StartGame.png", 800, 100, 300, 100};
    Button tutorial = {window.getRenderer(), "Assets/Button/Button_Tutorial.png", 800, 250, 300, 100};
    Button leaderboard = {window.getRenderer(), "Assets/Button/Button_Leaderboard.png", 800, 400, 300, 100};
    Button back = {window.getRenderer(), ""}

    // Clear
    window.clear();

    while (SDL_PollEvent(&event)) {
        // Quit
        if (event.type == SDL_QUIT) 
            gameRunning = false;
        // If not quit, check which mode player choose
        else if (startGame.isClicked(event)) {
            GameMenu(window);
        }
        else if (tutorial.isClicked(event)) {
            Tutorial(window);
        }
        else if (leaderboard.isClicked(event)) {
            Leaderboard(window);
        }
        else if (back.isClicked(event)) {
            break;
        }
    }
    // Render
    window.renderScreen(gameInit);
    startGame.renderButton();
    tutorial.renderButton();
    leaderboard.renderButton();

    // Display
    window.display();
}

void GameMenu(RenderWindow window) {
    SDL_Texture* gameMenu = window.loadTexture("Assets/Screen/Game_Init.png");
    Button startGame = {window.getRenderer(), "Assets/Button/Button_StartGame.png", 800, 100, 300, 100};
    Button tutorial = {window.getRenderer(), "Assets/Button/Button_Tutorial.png", 800, 250, 300, 100};
    Button leaderboard = {window.getRenderer(), "Assets/Button/Button_Leaderboard.png", 800, 400, 300, 100};
}

void Tutorial(RenderWindow window) {
    SDL_Texture* gameMenu = window.loadTexture("Assets/Screen/Game_Init.png");
    Button startGame = {window.getRenderer(), "Assets/Button/Button_StartGame.png", 800, 100, 300, 100};
    Button tutorial = {window.getRenderer(), "Assets/Button/Button_Tutorial.png", 800, 250, 300, 100};
    Button leaderboard = {window.getRenderer(), "Assets/Button/Button_Leaderboard.png", 800, 400, 300, 100};
}

void Leaderboard(RenderWindow window) {

}
#endif