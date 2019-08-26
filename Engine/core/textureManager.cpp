#include "./headers/textureManager.hpp"

void TextureManager::startUp() {
    if (TTF_Init() < 0) {
        std::cout << "ERROR: Could not initialize SDL TTF\n";
    }
}

void TextureManager::shutDown() {
    for (auto t : textures) {
        SDL_DestroyTexture(t.first);
    }
}

void TextureManager::render() {
    for (auto t : textures) {
        // Set rendering space and render to screen
        SDL_Rect renderQuad = { std::get<2>(t.second), std::get<3>(t.second), std::get<0>(t.second), std::get<1>(t.second)};
        SDL_RenderCopy(engine_ptr->getWindowManager()->getRenderer(), t.first, NULL, &renderQuad);
    }
}

void TextureManager::update(SDL_Event& e) {

}

void TextureManager::handleEvent(const SDL_Event& e) {

}

bool TextureManager::loadRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, int posx, int posy) {

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        std::cout << "Unable to render text surface. SDL_ttf ERROR: " << TTF_GetError() << "\n";
        return false;
    }

    // Create texture from surface pixels
    auto texture = SDL_CreateTextureFromSurface(engine_ptr->getWindowManager()->getRenderer(), textSurface);
    if (texture == NULL) {
        std::cout << "Unable to create texture from rendered text. SDL ERROR: " << SDL_GetError() << "\n";
        return false;
    }
    // Get image dimensions
    int width = textSurface->w;
    int height = textSurface->h;

    // Add the texture into the table
    textures.insert({ texture, std::make_tuple(width, height, posx, posy) });

    return true;
}

void TextureManager::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // TODO
}

void TextureManager::setBlendMode(SDL_BlendMode blending) {
    // TODO
}

void TextureManager::setAlpha(Uint8 alpha) {
    // TODO
}