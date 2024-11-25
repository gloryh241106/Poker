#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.h"

class Button {
    public:
        Button (SDL_Renderer* renderer, const char* p_buttonPath, int p_x, int p_y, int p_w, int p_h) {
            button_renderer = renderer;
            x = p_x;
            y = p_y;
            w = p_w;
            h = p_h;

            button_texture = resource.getTexture(p_buttonPath, renderer);
        }

        bool isClicked (SDL_Event &event) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
                if (event.button.button == SDL_BUTTON_LEFT)
                    return true;
            }

            return false;
        }

        void renderButton() {
            SDL_Rect buttonSize = {x, y, w, h};
            if (button_texture != NULL) {
                SDL_RenderCopy(button_renderer, button_texture, NULL, &buttonSize);
            }
        }

        void DestroyButton() {
            if (button_texture) 
                SDL_DestroyTexture(button_texture);
        }
        
    private:
        SDL_Renderer* button_renderer;
        SDL_Texture* button_texture;
        int x, y, w, h;
};