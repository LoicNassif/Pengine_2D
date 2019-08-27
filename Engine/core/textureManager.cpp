#include "./headers/textureManager.hpp"

void TextureManager::startUp() {
    if (TTF_Init() < 0) {
        std::cout << "ERROR: Could not initialize SDL TTF\n";
    }
}

void TextureManager::shutDown() {
    for (size_t i=0; i<textures.size(); i++) {
        SDL_DestroyTexture(std::get<0>(textures[i]));
    }
}

void TextureManager::render(SDL_Renderer* r) {
    for (size_t i=0; i<textures.size(); i++) {
        // Set rendering space and render to screen
        SDL_Rect renderQuad = { std::get<2>(std::get<1>(textures[i])), std::get<3>(std::get<1>(textures[i])), 
                                std::get<0>(std::get<1>(textures[i])), std::get<1>(std::get<1>(textures[i]))};
        SDL_RenderCopy(r, std::get<0>(textures[i]), NULL, &renderQuad);
    }
}

void TextureManager::update(SDL_Event& e) {

}

void TextureManager::handleEvent(const SDL_Event& e) {

}

void TextureManager::clearTexture(const std::string& s) {
    for (size_t i=0; i<textures.size(); i++) {
        if (std::get<4>(std::get<1>(textures[i])) == s) {
            SDL_DestroyTexture(std::get<0>(textures[i]));
            textures.erase(textures.begin() + i);
            break;
        }
    }
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
    textures.push_back(std::make_tuple( texture, std::make_tuple(width, height, posx, posy, textureText )));

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