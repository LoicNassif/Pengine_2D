// Position is top-left

#pragma once

#include "shape.hpp"

class Rectangle : public Shape {
    public:
        Rectangle(Vec2<double>&& position, Vec2<double>&& v, int m, int h, int w) : mv(v), mMass(m), mp(position), mh(h), mw(w) {}
        ~Rectangle() {}

        /* Render */
        void render(SDL_Renderer &renderer) const override;

        /* modifications */
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setPos(const Vec2<double>& p) override { mp = p; }
        void setXPos(const double px) override { mp.x = px; }
        void setYPos(const double py) override { mp.y = py; }
        void setXVel(double vx) override { mv.x = vx; }
        void setYVel(double vy) override { mv.y = vy; }

        // Getters
        Vec2<double> getPosition() const override;
        Vec2<double> getVelocity() const override;
        int getMass() const override { return mMass; }
        double getHeight() const { return mh; }
        double getWidth() const { return mw; }  

    private:
        Vec2<double> mp;
        Vec2<double> mv;

        double mh;
        double mw;
        int mMass;
};