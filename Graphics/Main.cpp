#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"
#include "Utils.h"

int main(int argc, char* args[]) {
    // Checking if initialize get error
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        std::cout << "Failed to load. Error: " << SDL_GetError() << '\n';
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "Failed to load image. Error: " << SDL_GetError() << '\n';
    }

    // Create window and gameRunning
    RenderWindow window("Poker", 1280, 720);
    bool gameRunning = true;
    
    // Load event and texture
    SDL_Event event;
    SDL_Texture* gameMenu = window.loadTexture("gfs/Screen/Game_Init.png");
    SDL_Texture* buttonStartGame = window.loadTexture("gfs/Screen/Button/Button_StartGame.png");

    // Create entities (Buttons)
    Entity entities[3] = {Entity(1000, 200, gameMenu), Entity(30, 0, gameMenu), Entity(60, 0, gameMenu)};

    // Initializing variables for checking frame time
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while (gameRunning) {
        // Get frame time
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        // Handle event
        while (accumulator >= timeStep) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) 
                    gameRunning = false;
            }

            accumulator -= timeStep;
        }

        // Render and display image, entities
        window.clear();
        window.render(gameMenu);
        window.display();

        // Checking time and get delay for better gameplay
        int frameTicks = SDL_GetTicks() - startTicks;

        // Delay time for fit with computer frame time
        if (frameTicks < 1000 / window.getRefreshRate()) {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }
    
    // After exit, destroy all window and quit SDL2
    window.cleanUp();
    SDL_Quit();

    // Exit code
    return 0;
}