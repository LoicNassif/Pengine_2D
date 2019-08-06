#pragma once

#include "shape.hpp"

class Circle : public Shape {
    public:
        Circle(Vec2<int>& center, int r, Vec2<int>& v, int m) : mCenter(center), mr(r), mv(v), mMass(m) { }
        ~Circle() {}

        /* Render */
        void render(SDL_Renderer& renderer) const override;

        /* modifications */
        void move(const Vec2<int> &distance, int width, int height, const std::vector<Shape *> &objs) override;
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setCenter(const Vec2<int> &v) override;
        void setXVel(int vx) override { mv.x = vx; }
        void setYVel(int vy) override { mv.y = vy; }

        // Getters
        Vec2<int> getCenter() const override;
        Vec2<int> getVelocity() const override;
        int getRadius() const { return mr; }
        int getMass() const override { return mMass; }

    private:
        Vec2<int> mCenter;
        Vec2<int> mv;
        int mr;
        int mMass;
};