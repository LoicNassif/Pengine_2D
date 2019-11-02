#pragma once
#ifdef _WIN32
    #include <SDL2_ttf-2.0.15/SDL_ttf.h>
#endif
#include <unordered_map>

#include "engine.hpp"

class Engine;

class TextureManager {
    public:
        TextureManager(const Engine* e) : engine_ptr(e) {}
        ~TextureManager() {}

        // Texture manager start-up
        void startUp();

        // Texture manager shut-down
        void shutDown();

        // Update and handle events
        void render(SDL_Renderer* r);
        void update(SDL_Event& e);
        void handleEvent(const SDL_Event& e);
        void clearTexture(const std::string& s);

        // bool loadRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, int posx, int posy);

        // Setters
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);

    private:
        // Engine instance
        const Engine* engine_ptr = nullptr;

        // Hold a list of textures to be rendered with their dimensions
        std::vector<std::tuple<SDL_Texture*, std::tuple<int, int, int, int, std::string>>> textures;
};