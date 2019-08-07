#include "./headers/circle.hpp"
#include <cmath>

/* TEST MOVE LATER */
int dt = 2;

bool detect_circle_collisions(Circle* a, Circle* b) {
    Vec2<int> b_coord = b->getCenter();
    Vec2<int> a_coord = a->getCenter();

    int ub = (b->getRadius() + a->getRadius()) * (b->getRadius() + a->getRadius());
    int lb = (b->getRadius() - a->getRadius()) * (b->getRadius() - a->getRadius());
    int intersec = (b_coord.x - a_coord.x) * (b_coord.x - a_coord.x) + (b_coord.y - a_coord.y) * (b_coord.y - a_coord.y);

    return (intersec < ub);
}

void elastic_collision(Circle* a, Circle* b) {
    double m_a = a->getMass(); double m_b = b->getMass();
    Vec2<int> v_a = a->getVelocity(); Vec2<int> v_b = b->getVelocity();

    /* x direction */
    double Ax = m_a * v_a.x + m_b * v_b.x;
    double Bx = 0.5 * m_a * v_a.x * v_a.x + 0.5 * m_b * v_b.x * v_b.x;
    double sqrt_dx = std::sqrt(m_a * m_b * (2 * m_a * Bx + 2 * m_b * Bx - Ax * Ax)); 
    double vx_a = (Ax * m_a - sqrt_dx) / (m_a * (m_a + m_b));
    double vx_b = (Ax * m_b + sqrt_dx) / (m_b * (m_a + m_b));
    a->setXVel(vx_a); b->setXVel(vx_b);

    /* y direction */
    double Ay = m_a * v_a.y + m_b * v_b.y;
    double By = 0.5 * m_a * v_a.y * v_a.y + 0.5 * m_b * v_b.y * v_b.y;
    double sqrt_dy = std::sqrt(m_a * m_b * (2 * m_a * By + 2 * m_b * By - Ay * Ay));
    double vy_a = (Ay * m_a - sqrt_dy) / (m_a * (m_a + m_b));
    double vy_b = (Ay * m_b + sqrt_dy) / (m_b * (m_a + m_b)); 
    a->setYVel(vy_a); b->setYVel(vy_b);
}

void draw_circle(int x, int y, int p, int q, SDL_Renderer &ren)
{
    SDL_RenderDrawPoint(&ren, x + p, y + q);
    SDL_RenderDrawPoint(&ren, x - p, y + q);
    SDL_RenderDrawPoint(&ren, x + p, y - q);
    SDL_RenderDrawPoint(&ren, x - p, y - q);

    SDL_RenderDrawPoint(&ren, x + q, y + p);
    SDL_RenderDrawPoint(&ren, x - q, y + p);
    SDL_RenderDrawPoint(&ren, x + q, y - p);
    SDL_RenderDrawPoint(&ren, x - q, y - p);
}

void Circle::render(SDL_Renderer& renderer) const {
    // Perform the Bresenham's algorithm
    int p = 0; int q = mr; int d = 3 - 2*mr;
    draw_circle(mCenter.x, mCenter.y, p, q, renderer);
    while (p <= q) {
        p++;
        if (d < 0) {
            d = d + 4*p + 6;
        } else {
            d = d + 4*(p-q) + 10;
            q--;
        }
        draw_circle(mCenter.x, mCenter.y, p, q, renderer);
    }
}

void Circle::move(int width, int height, const std::vector<Shape *>& objs) {
    /* Check object contraints */
    for (Shape *s : objs)
    {
        if (this != s)
        {
            while (detect_circle_collisions(this, static_cast<Circle *>(s)))
            {
                elastic_collision(this, static_cast<Circle *>(s));
                Vec2<int> sNewPos = s->getCenter() + s->getVelocity() * dt;
                if (sNewPos.x + mr < width && sNewPos.x - mr > 0 && sNewPos.y - mr > 0 && sNewPos.y + mr < height)
                {
                    s->setCenter(sNewPos);
                }
                mCenter = mCenter + mv*dt;
                while (detect_circle_collisions(this, static_cast<Circle *>(s))) {
                    if (s->getCenter().x >= mCenter.x) { // On the right
                        mCenter.x--;
                    } else { // On the left
                        mCenter.x++;
                    }
                    if (s->getCenter().y >= mCenter.y) { // On the bottom
                        mCenter.y--;
                    } else { // On the top
                        mCenter.y++;
                    }
                }
            }
            int sRadius = s->getRadius(); 
            if (s->getCenter().x + sRadius >= width)
            { // right boundary
                int rb = s->getCenter().x - sRadius - 2; 
                s->setXCenter(rb);
            }
            if (s->getCenter().x - sRadius <= 0)
            { // left boundary
                int lb = s->getCenter().x + sRadius + 2;
                s->setXCenter(lb);
            }
            if (s->getCenter().y + sRadius >= height)
            { // bottom boundary
                int bb = s->getCenter().y - sRadius - 2;
                s->setXCenter(bb);
            }
            if (s->getCenter().y - sRadius <= 0)
            { // top boundary
                int tb = s->getCenter().y + sRadius + 2;
                s->setXCenter(tb);
            }
            if (s->getCenter().x + s->getRadius() >= width || s->getCenter().x - s->getRadius() <= 0)
            {
                s->setXVel(-s->getVelocity().x);
            }
            if (s->getCenter().y + s->getRadius() >= height || s->getCenter().y - s->getRadius() <= 0)
            {
                s->setYVel(-s->getVelocity().y);
            }
        }
    }
    Vec2<int> newPos = mCenter + mv * dt;
    /* Check wall constraints */
    if (newPos.x + mr < width && newPos.x - mr > 0 && newPos.y - mr > 0 && newPos.y + mr < height)
    {
        mCenter = newPos;
    }
    if (mCenter.x + mr >= width) { // right boundary
        mCenter.x = width - mr - 2;
    }
    if (mCenter.x - mr <= 0) { // left boundary
        mCenter.x = 0 + mr + 2;
    }
    if (mCenter.y + mr >= height) { // bottom boundary
        mCenter.y = height - mr - 2;
    }
    if (mCenter.y - mr <= 0) { // top boundary
        mCenter.y = 0 + mr + 2;
    }
    if (newPos.x + mr >= width || newPos.x - mr <= 0)
    {
        mv.x = -mv.x;
    }
    if (newPos.y + mr >= height || newPos.y - mr <= 0)
    {
        mv.y = -mv.y;
    }
}

void Circle::rotate(int angle) {
    // TODO
}

void Circle::resize(int factor) {
    // TODO
}

void Circle::setCenter(const Vec2<int> &v) {
    mCenter = v;
}

Vec2<int> Circle::getCenter() const {
    return mCenter;
}

Vec2<int> Circle::getVelocity() const {
    return mv;
}