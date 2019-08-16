#pragma once
#include <SDL.h>
#undef main
#include <vector>
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
        virtual void setCenter(const Vec2<double>& v) = 0;
        virtual void setXCenter(double x) = 0;
        virtual void setYCenter(double y) = 0;
        virtual void setXVel(double vx) = 0;
        virtual void setYVel(double vy) = 0;

        // Getters
        virtual Vec2<double> getCenter() const = 0;
        virtual Vec2<double> getVelocity() const = 0;
        virtual int getRadius() const = 0; 
        virtual int getMass() const = 0;
};