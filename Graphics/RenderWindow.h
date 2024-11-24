#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.h"

class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_width, int p_height);
        SDL_Texture* loadTexture(const char* p_filePath);
        int getRefreshRate();
        void cleanUp();
        void clear();
        void render(SDL_Texture* p_texture);
        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};