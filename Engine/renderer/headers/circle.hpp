#pragma once

#include "shape.hpp"

class Circle : public Shape {
    public:
        Circle(Vec2<double>& center, int r, Vec2<double>& v, int m) : mCenter(center), mr(r), mv(v), mMass(m) { }
        Circle(Vec2<double> &&center, int r, Vec2<double> &&v, int m) : mCenter(center), mr(r), mv(v), mMass(m) {}
        ~Circle() {}

        /* Render */
        void render(SDL_Renderer& renderer) const override;

        /* modifications */
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setCenter(const Vec2<double> &v) override;
        void setXCenter(double x) override {mCenter.x = x;}
        void setYCenter(double y) override {mCenter.y = y;}
        void setXVel(double vx) override { mv.x = vx; }
        void setYVel(double vy) override { mv.y = vy; }
        void switchXInWall() { in_wallx = !in_wallx; }
        void switchYInWall() { in_wally = !in_wally; }

        // Getters
        Vec2<double> getCenter() const override;
        Vec2<double> getVelocity() const override;
        int getRadius() const { return mr; }
        int getMass() const override { return mMass; }
        int getXInWall() const { return in_wallx; }
        int getYInWall() const { return in_wally; }

    private:
        Vec2<double> mCenter;
        Vec2<double> mv;
        int mr;
        int mMass;

        bool in_wallx = false;
        bool in_wally = false;
};