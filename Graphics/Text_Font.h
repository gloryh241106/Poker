#ifndef __TEXT_FONT__
#define __TEXT_FONT__

#include <SDL2/SDL_ttf.h>
#include <iostream>

// Create font
class Text_Font {
    public:
        Text_Font (SDL_Renderer* renderer, const char* p_text) {
            if (TTF_Init() == -1) 
                std::cerr << "Failed to initialize font! TTF_Error: " << TTF_GetError() << '\n';

            text = p_text;
            text_renderer = renderer;
            
            TTF_Font* font = TTF_OpenFont("Arial.ttf", 24); 
            if (font == NULL) {
                std::cerr << "Failed to create font! TTF_Error: " << TTF_GetError() << '\n';
                TTF_Quit();
            }

            SDL_Color textColor = {255, 0, 0};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, p_text, textColor);
            if (textSurface == NULL) {
                std::cerr << "Failed to render font! TTF_Error: " << TTF_GetError() << '\n';
                TTF_CloseFont(font);
                TTF_Quit();
            }
        }
        
        void renderText() {
            SDL_Rect renderQuad = {100, 100, 200, 50}; // Vị trí và kích thước
            SDL_RenderCopy(text_renderer, NULL, &renderQuad);
        }
    private:
        const char* text;
        SDL_Renderer* text_renderer;
};

#endif