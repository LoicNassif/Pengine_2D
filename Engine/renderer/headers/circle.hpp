// Position is the center

#pragma once

#include "shape.hpp"

class Circle : public Shape {
    public:
        Circle(Vec2<double>& position, int r, Vec2<double>& v, int m) : mp(position), mr(r), mv(v), mMass(m) { }
        Circle(Vec2<double> &&position, int r, Vec2<double> &&v, int m) : mp(position), mr(r), mv(v), mMass(m) {}
        ~Circle() {}

        /* Render */
        void render(SDL_Renderer& renderer) const override;

        /* modifications */
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setPos(const Vec2<double> &p) override { mp = p; };
        void setXPos(double x) override {mp.x = x;}
        void setYPos(double y) override {mp.y = y;}
        void setXVel(double vx) override { mv.x = vx; }
        void setYVel(double vy) override { mv.y = vy; }
        void switchXInWall() { in_wallx = !in_wallx; }
        void switchYInWall() { in_wally = !in_wally; }

        // Getters
        Vec2<double> getPosition() const override;
        Vec2<double> getVelocity() const override;
        int getRadius() const { return mr; }
        int getMass() const override { return mMass; }
        int getXInWall() const { return in_wallx; }
        int getYInWall() const { return in_wally; }

    private:
        Vec2<double> mp;
        Vec2<double> mv;
        int mr;
        int mMass;

        bool in_wallx = false;
        bool in_wally = false;
};