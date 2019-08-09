#pragma once

#include "shape.hpp"

class Circle : public Shape {
    public:
        Circle(Vec2<int>& center, int r, Vec2<double>& v, int m) : mCenter(center), mr(r), mv(v), mMass(m) { }
        ~Circle() {}

        /* Render */
        void render(SDL_Renderer& renderer) const override;

        /* modifications */
        void move(int width, int height, const std::vector<Shape *> &objs) override;
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setCenter(const Vec2<int> &v) override;
        void setXCenter(int x) override {mCenter.x = x;}
        void setYCenter(int y) override {mCenter.y = y;}
        void setXVel(int vx) override { mv.x = vx; }
        void setYVel(int vy) override { mv.y = vy; }

        // Getters
        Vec2<int> getCenter() const override;
        Vec2<double> getVelocity() const override;
        int getRadius() const override { return mr; }
        int getMass() const override { return mMass; }

    private:
        Vec2<int> mCenter;
        Vec2<double> mv;
        int mr;
        int mMass;
};