#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

#include "Entity.h"

class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_w, int p_h) : window (NULL) , renderer(NULL) {
            window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
            if (window == NULL) 
                std::cout << "Failed to create window. Error: " << SDL_GetError() << '\n';
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        };

        SDL_Texture* loadTexture(const char* p_filePath) {
            // Check if texture already exists in cache
            if (textureCache.find(p_filePath) != textureCache.end()) 
                return textureCache[p_filePath];

            // If not, create a new texture
            SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath);

            // Checking if initializing is error
            if (texture == NULL) 
                std::cout << "Failed to load texture. Error: " << SDL_GetError() << '\n';
            else 
                // Save to cache
                textureCache[p_filePath] = texture; 

            return texture;
        }

        SDL_Renderer* getRenderer() {
            return renderer;
        }

        void clear() {
            SDL_RenderClear(renderer);
        }

        // Releases cache
        void freeTextures() {
            for (auto& pair : textureCache) 
                SDL_DestroyTexture(pair.second);

            textureCache.clear();
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
        std::unordered_map<std::string, SDL_Texture*> textureCache;
};