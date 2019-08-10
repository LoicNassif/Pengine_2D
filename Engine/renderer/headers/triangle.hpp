#pragma once

#include "shape.hpp"

class Triangle : public Shape {
    public:
        // TODO: make a vertex class to hold shape vertices
        Triangle(Vec2<int>& center, int p1, int p2, int p3, Vec2<double>& v, int m) : mCenter(center), mv(v), mMass(m) {}
        ~Triangle() {}

        /* Render */
        void render(SDL_Renderer &renderer) const override;

        /* modifications */
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setCenter(const Vec2<int> &v) override;
        void setXCenter(int x) override { mCenter.x = x; }
        void setYCenter(int y) override { mCenter.y = y; }
        void setXVel(int vx) override { mv.x = vx; }
        void setYVel(int vy) override { mv.y = vy; }

        // Getters
        Vec2<int> getCenter() const override;
        Vec2<double> getVelocity() const override;
        int getMass() const override { return mMass; }

    private:
        Vec2<int> mCenter;
        Vec2<double> mv;
        int mMass;
};
