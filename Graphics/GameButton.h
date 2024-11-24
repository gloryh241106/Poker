#ifndef __GAMEBUTTON__
#define __GAMEBUTTON__

#include "RenderWindow.h"
#include "RenderButton.h"

void StartGame(RenderWindow window) {
    // Render and display image, entities
    SDL_Texture* gameMenu = window.loadTexture("Assets/Screen/Game_Init.png");
    Button startGame = {window.getRenderer(), "Assets/Button/Button_StartGame.png", 800, 100, 300, 100};
    Button tutorial = {window.getRenderer(), "Assets/Button/Button_Tutorial.png", 800, 250, 300, 100};
    Button leaderboard = {window.getRenderer(), "Assets/Button/Button_Leaderboard.png", 800, 400, 300, 100};

    // Clear
    window.clear();

    // Render
    window.renderScreen(gameMenu);
    startGame.renderButton();
    tutorial.renderButton();
    leaderboard.renderButton();

    // Display
    window.display();
}

#endif