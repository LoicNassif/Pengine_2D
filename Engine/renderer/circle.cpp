#include "./headers/circle.hpp"

void draw_circle(int x, int y, int p, int q, SDL_Renderer &ren)
{
    // std::cout << "drawing!" << std::endl;
    SDL_RenderDrawPoint(&ren, x + p, y + q);
    SDL_RenderDrawPoint(&ren, x - p, y + q);
    SDL_RenderDrawPoint(&ren, x + p, y - q);
    SDL_RenderDrawPoint(&ren, x - p, y - q);

    SDL_RenderDrawPoint(&ren, x + q, y + p);
    SDL_RenderDrawPoint(&ren, x - q, y + p);
    SDL_RenderDrawPoint(&ren, x + q, y - p);
    SDL_RenderDrawPoint(&ren, x - q, y - p);
}

void Circle::render(SDL_Renderer& renderer) const {
    // Perform the Bresenham's algorithm
    int p = 0; int q = mr; int d = 3 - 2*mr;
    draw_circle(mCenter.x, mCenter.y, p, q, renderer);
    while (p <= q) {
        p++;
        if (d < 0) {
            d = d + 4*p + 6;
        } else {
            d = d + 4*(p-q) + 10;
            q--;
        }
        draw_circle(mCenter.x, mCenter.y, p, q, renderer);
    }
}

void Circle::move(const Vec2<int> &destination) {
    mCenter = mCenter + destination;
}

void Circle::rotate(int angle) {
    // TODO
}

void Circle::resize(int factor) {
    // TODO
}

void Circle::setCenter(const Vec2<int> &v) {
    mCenter = v;
}

Vec2<int> Circle::getCenter() const {
    return mCenter;
}