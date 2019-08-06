#pragma once

#include "shape.hpp"

class Circle : public Shape {
    public:
        Circle(Vec2<int>& center, int r) : mCenter(center), mr(r) { }
        ~Circle() {}

        /* Render */
        void render(SDL_Renderer& renderer) const override;

        /* modifications */
        void move(const Vec2<int> &destination) override;
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setCenter(const Vec2<int> &v) override;

        // Getters
        Vec2<int> getCenter() const override;

    private:
        Vec2<int> mCenter;
        int mr;
};