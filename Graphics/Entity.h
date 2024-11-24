#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
    public:
        Entity(float p_x, float p_y, SDL_Texture* p_texture) : x(p_x), y(p_y), texture(p_texture) {
            currentFrame.x = 0;
            currentFrame.y = 0;
            currentFrame.w = 300;
            currentFrame.h = 100;
        }

        float getX() {
            return x;
        }

        float getY() {
            return y;
        }

        SDL_Texture* getTexture() {
            return texture;
        }

        SDL_Rect getCurrentFrame() {
            return currentFrame;
        }

    private:
        float x, y;
        SDL_Rect currentFrame;
        SDL_Texture* texture;
};