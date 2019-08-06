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
        virtual void move(const Vec2<int> &distance, int width, int height, const std::vector<Shape *> &objs) = 0;
        virtual void rotate(int angle) = 0;
        virtual void resize(int factor) = 0;

        // Setters
        virtual void setCenter(const Vec2<int>& v) = 0;
        virtual void setXVel(int vx) = 0;
        virtual void setYVel(int vy) = 0;

        // Getters
        virtual Vec2<int> getCenter() const = 0;
        virtual Vec2<int> getVelocity() const = 0;
        virtual int getMass() const = 0;
};