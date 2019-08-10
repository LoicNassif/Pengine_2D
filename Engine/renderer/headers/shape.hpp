#pragma once
#include <SDL.h>
#undef main
#include "../../math/vec2.hpp"

class Shape {
    public:
        virtual ~Shape() {}

        /* Render */
        virtual void render(SDL_Renderer &renderer) const = 0;

        /* modifications */
        virtual void rotate(int angle) = 0;
        virtual void resize(int factor) = 0;

        // Setters
        virtual void setCenter(const Vec2<int>& v) = 0;
        virtual void setXCenter(int x) = 0;
        virtual void setYCenter(int y) = 0;
        virtual void setXVel(int vx) = 0;
        virtual void setYVel(int vy) = 0;

        // Getters
        virtual Vec2<int> getCenter() const = 0;
        virtual Vec2<double> getVelocity() const = 0;
        virtual int getMass() const = 0;
};