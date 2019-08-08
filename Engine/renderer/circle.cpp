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
    Vec2<int> c_a = a->getCenter(); Vec2<int> c_b = b->getCenter();

    double distance = std::sqrt((c_a.x - c_b.x) * (c_a.x - c_b.x) + (c_a.y - c_b.y) * (c_a.y - c_b.y));

    double nx = (c_b.x - c_a.x) / distance;
    double ny = (c_b.y - c_a.y) / distance;
    double kx = v_a.x - v_b.x;
    double ky = v_a.y - v_b.y;

    double p = 2.0 * (nx * kx + ny * ky) / (m_b + m_a);
    double v_afx = v_a.x - p * m_b * nx;
    double v_afy = v_a.y - p * m_b * ny;
    double v_bfx = v_b.x + p * m_a * nx;
    double v_bfy = v_b.y + p * m_a * ny;

    a->setXVel(v_afx); a->setYVel(v_afy);
    b->setXVel(v_bfx); b->setYVel(v_bfy);
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
            if (detect_circle_collisions(this, static_cast<Circle *>(s)))
            {
                elastic_collision(this, static_cast<Circle *>(s));
                Vec2<int> sNewPos = s->getCenter() + s->getVelocity() * dt;
                if (sNewPos.x + mr < width && sNewPos.x - mr > 0 && sNewPos.y - mr > 0 && sNewPos.y + mr < height)
                {
                    s->setCenter(sNewPos);
                }
                mCenter = mCenter + mv*dt;
                if (detect_circle_collisions(this, static_cast<Circle *>(s))) {
                    // Static collision resolution
                    double distance = std::sqrt((s->getCenter().x - mCenter.x) * (s->getCenter().x - mCenter.x) 
                                                + (s->getCenter().y - mCenter.y) * (s->getCenter().y - mCenter.y));
                    double overlap = 0.5 * (distance - mr - s->getRadius());

                    // Displace current circle
                    mCenter.x -= overlap * (mCenter.x - s->getCenter().x) / distance;
                    mCenter.y -= overlap * (mCenter.y - s->getCenter().y) / distance;

                    // Displace other circle
                    s->setXCenter(s->getCenter().x + overlap * (mCenter.x - s->getCenter().x) / distance);
                    s->setYCenter(s->getCenter().y + overlap * (mCenter.y - s->getCenter().y) / distance);
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