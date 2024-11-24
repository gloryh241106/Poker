#include "Entity.h"

Entity::Entity(float p_x, float p_y, SDL_Texture* p_texture) : x(p_x), y(p_y), texture(p_texture) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 300;
    currentFrame.h = 100;
}

float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}