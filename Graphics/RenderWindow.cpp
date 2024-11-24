#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) : window (NULL) , renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL) 
        std::cout << "Failed to create window. Error: " << SDL_GetError() << '\n';
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
};

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL) 
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << '\n';

    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

int RenderWindow::getRefreshRate() {
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::render(SDL_Texture* p_texture) {
    // // The small image need to be copied
    // SDL_Rect src;
    // src.x = p_entity.getCurrentFrame().x;
    // src.y = p_entity.getCurrentFrame().y;
    // src.w = p_entity.getCurrentFrame().w;
    // src.h = p_entity.getCurrentFrame().h;

    // // The place where the image should be pasted
    // SDL_Rect dst;
    // dst.x = p_entity.getX() * 4;
    // dst.y = p_entity.getY() * 4;
    // dst.w = p_entity.getCurrentFrame().w * 4;
    // dst.h = p_entity.getCurrentFrame().h * 4;
    SDL_RenderCopy(renderer, p_texture, NULL, NULL);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}