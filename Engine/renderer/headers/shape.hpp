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
        virtual void setPos(const Vec2<double>& v) = 0;
        virtual void setXPos(double x) = 0;
        virtual void setYPos(double y) = 0;
        virtual void setXVel(double vx) = 0;
        virtual void setYVel(double vy) = 0;

        // Getters
        virtual Vec2<double> getPosition() const = 0;
        virtual Vec2<double> getVelocity() const = 0;
        virtual int getMass() const = 0;
};