#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

#include "Resources.h"

// Let resource here for rendering windows
Resources resource;

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h) : window (NULL) , renderer(NULL) {
        window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
        if (window == NULL) 
            std::cout << "Failed to create window. Error: " << SDL_GetError() << '\n';
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    };

    SDL_Texture* loadTexture(const char* p_filePath) {             
        return resource.getTexture(p_filePath, renderer);
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

    void clear() {
        SDL_RenderClear(renderer);
    }

    // Releases cache
    void freeTextures() {
        resource.clearTextures();
    }

    void cleanUp() {
        freeTextures();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    // Get the refresh rate, for example 60Hz
    int getRefreshRate() {
        int displayIndex = SDL_GetWindowDisplayIndex(window);
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(displayIndex, 0, &mode);

        return mode.refresh_rate;
    }

    void renderScreen(SDL_Texture* p_screen) {
        // Render
        SDL_RenderCopy(renderer, p_screen, NULL, NULL);
    }
    
    void display() {
        SDL_RenderPresent(renderer);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};