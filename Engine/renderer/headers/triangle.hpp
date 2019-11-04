// Position is top middle

#pragma once

#include "shape.hpp"

class Triangle : public Shape {
    public:
        Triangle(Vec2<double>& position, Vec2<double>& v, int m) : mp(position), mv(v), mMass(m) {}
        ~Triangle() {}

        /* Render */
        void render(SDL_Renderer &renderer) const override;

        /* modifications */
        void rotate(int angle) override;
        void resize(int factor) override;

        // Setters
        void setPos(const Vec2<double> &v) override;
        void setXPos(double x) override { mp.x = x; }
        void setYPos(double y) override { mp.y = y; }
        void setXVel(double vx) override { mv.x = vx; }
        void setYVel(double vy) override { mv.y = vy; }

        // Getters
        Vec2<double> getPosition() const override;
        Vec2<double> getVelocity() const override;
        int getMass() const override { return mMass; }

    private:
        Vec2<double> mp;
        Vec2<double> mv;
        int mMass;
};
