#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>



class Resources {
public:
    SDL_Texture* addTexture(const char* p_filePath, SDL_Renderer* renderer) {
        // Load the texture using SDL_image
        SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath);

        // Checking if texture is error
        if (texture == NULL) {
            std::cerr << "Failed to load texture: " << p_filePath << ". Error: " << IMG_GetError() << std::endl;
            return NULL;
        }

        // If not, returnn the texture created and add it in the textureCache
        textureCache[p_filePath] = texture;
        return texture;
    }

    // Get a texture resource
    SDL_Texture* getTexture(const char* p_filePath, SDL_Renderer* renderer) {
        // Check if the texture is already cached
        auto it = textureCache.find(p_filePath);
        if (it != textureCache.end()) {
            return it->second; 
        }

        // If not founded, then we create a new one and return the new texture
        else return addTexture (p_filePath, renderer);
    }

    // Remove a specific texture resource for the next renderer
    void removeTexture(const char* p_filePath) {
        auto it = textureCache.find(p_filePath);
        if (it != textureCache.end()) {
            SDL_DestroyTexture(it->second);
            textureCache.erase(it);
        }
    }

    // Clear all cached textures
    void clearTextures() {
        for (auto &pair : textureCache) {
            SDL_DestroyTexture(pair.second);
        }
        textureCache.clear();
        std::cout << "All textures cleared." << std::endl;
    }

private:
    std::unordered_map<const char*, SDL_Texture*> textureCache; 
};