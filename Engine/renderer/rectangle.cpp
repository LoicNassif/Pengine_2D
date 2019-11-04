#include "headers/rectangle.hpp"

void Rectangle::render(SDL_Renderer& ren) const {
    SDL_RenderDrawLine(&ren, mp.x, mp.y, mp.x + mw, mp.y); // Top edge
    SDL_RenderDrawLine(&ren, mp.x + mw, mp.y, mp.x + mw, mp.y + mh); // Right edge
    SDL_RenderDrawLine(&ren, mp.x, mp.y + mh, mp.x + mw, mp.y + mh); // Bottom edge
    SDL_RenderDrawLine(&ren, mp.x, mp.y, mp.x, mp.y + mh); // Left edge
}

void Rectangle::rotate(int angle) {
    // TODO
}

void Rectangle::resize(int factor) {
    // TODO
}

Vec2<double> Rectangle::getPosition() const {
    return mp;
}

Vec2<double> Rectangle::getVelocity() const {
    return mv;
}

