#include "headers/physicsManager.hpp"

void PhysicsManager::startUp() {

}

void PhysicsManager::update(SDL_Event& e) {
    
}

void PhysicsManager::shutDown() {

}

bool PhysicsManager::checkCircularCollision(Circle* a, Circle* b) {
    Vec2<int> b_coord = b->getCenter();
    Vec2<int> a_coord = a->getCenter();

    int ub = (b->getRadius() + a->getRadius()) * (b->getRadius() + a->getRadius());
    int lb = (b->getRadius() - a->getRadius()) * (b->getRadius() - a->getRadius());
    int intersec = (b_coord.x - a_coord.x) * (b_coord.x - a_coord.x) + (b_coord.y - a_coord.y) * (b_coord.y - a_coord.y);

    return (intersec < ub);
}

void PhysicsManager::elasticCollision(Circle* a, Circle* b) {
    double m_a = a->getMass();
    double m_b = b->getMass();
    Vec2<double> v_a = a->getVelocity();
    Vec2<double> v_b = b->getVelocity();
    Vec2<int> c_a = a->getCenter();
    Vec2<int> c_b = b->getCenter();

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

    a->setXVel(v_afx);
    a->setYVel(v_afy);
    b->setXVel(v_bfx);
    b->setYVel(v_bfy);
}

void PhysicsManager::moveObject(Shape* target) {
    if (Circle* tCircle = dynamic_cast<Circle*>(target)) {
        moveObject(tCircle);
    }
}

void PhysicsManager::moveObject(Circle* target) {
    bool haveICollided = false;
    int width = engine_ptr->getWindowManager()->getWindowWidth();
    int height = engine_ptr->getWindowManager()->getWindowHeight();
    int tRadius = target->getRadius();
    /* Check object contraints */
    for (Shape *s : objects) {
        if (target != s) {
            if (Circle* sCircle = dynamic_cast<Circle*>(s)) { // Circle-Circle collision
                if (checkCircularCollision(target, sCircle)) {
                    haveICollided = true;
                    int sRadius = sCircle->getRadius();

                    // Elastic collision (computes new velocities)
                    elasticCollision(target, sCircle);
                    
                    // Set and check if the new values are within the borders of the screen
                    Vec2<int> sNewPos = sCircle->getCenter() + sCircle->getVelocity() * m_dt;
                    if (sNewPos.x + sRadius < width && sNewPos.x - sRadius > 0 && sNewPos.y - sRadius > 0 && sNewPos.y + sRadius < height) {
                        sCircle->setCenter(sNewPos);
                    }
                    if (sNewPos.x + sRadius >= width) { // right boundary
                        sCircle->setXCenter(width - sRadius - 2);
                        sCircle->setXVel(-sCircle->getVelocity().x);
                    }
                    if (sNewPos.x - sRadius <= 0) { // left boundary
                        sCircle->setXCenter(0 + sRadius + 2);
                        sCircle->setXVel(-sCircle->getVelocity().x);
                    }
                    if (sNewPos.y + sRadius >= height) { // bottom boundary
                        sCircle->setYCenter(height - sRadius - 2);
                        sCircle->setYVel(-sCircle->getVelocity().y);
                    }
                    if (sNewPos.y - sRadius <= 0) { // top boundary
                        sCircle->setYCenter(0 + sRadius + 2);
                        sCircle->setYVel(-sCircle->getVelocity().y);
                    }

                    Vec2<int> tNewPos = target->getCenter() + target->getVelocity()*m_dt;
                    if (tNewPos.x + tRadius < width && tNewPos.x - tRadius > 0 && tNewPos.y - tRadius > 0 && tNewPos.y + tRadius < height)
                    {
                        target->setCenter(tNewPos);
                    }
                    if (tNewPos.x + tRadius >= width)
                    { // right boundary
                        target->setXCenter(width - tRadius - 2);
                        target->setXVel(-target->getVelocity().x);
                    }
                    if (tNewPos.x - tRadius <= 0)
                    { // left boundary
                        target->setXCenter(0 + tRadius + 2);
                        target->setXVel(-target->getVelocity().x);
                    }
                    if (tNewPos.y + tRadius >= height)
                    { // bottom boundary
                        target->setYCenter(height - tRadius - 2);
                        target->setYVel(-target->getVelocity().y);
                    }
                    if (tNewPos.y - tRadius <= 0)
                    { // top boundary
                        target->setYCenter(0 + tRadius + 2);
                        target->setYVel(-target->getVelocity().y);
                    }

                    // Static collision resolution
                    if (checkCircularCollision(target, sCircle)) {
                        double distance = std::sqrt((sCircle->getCenter().x - target->getCenter().x) * (sCircle->getCenter().x - target->getCenter().x)
                                                    + (sCircle->getCenter().y - target->getCenter().y) * (sCircle->getCenter().y - target->getCenter().y));
                        double overlap = 0.5 * (distance - tRadius - sRadius);

                        // Displace target circle
                        target->setXCenter(target->getCenter().x - overlap * (target->getCenter().x - sCircle->getCenter().x) / distance);
                        target->setYCenter(target->getCenter().y - overlap * (target->getCenter().y - sCircle->getCenter().y) / distance);

                        // Displace other circle
                        sCircle->setXCenter(sCircle->getCenter().x + overlap * (target->getCenter().x - sCircle->getCenter().x) / distance);
                        sCircle->setYCenter(sCircle->getCenter().y + overlap * (target->getCenter().y - sCircle->getCenter().y) / distance);
                    }
                }
            }
        }
    }

    /* Check boundary contraints only if there was no collision */
    if (!haveICollided) {
        Vec2<int> tNewPos = target->getCenter() + target->getVelocity() * m_dt;
        if (tNewPos.x + tRadius < width && tNewPos.x - tRadius > 0 && tNewPos.y - tRadius > 0 && tNewPos.y + tRadius < height)
        {
            target->setCenter(tNewPos);
        }
        if (tNewPos.x + tRadius >= width)
        { // right boundary
            target->setXCenter(width - tRadius - 2);
            target->setXVel(-target->getVelocity().x);
        }
        if (tNewPos.x - tRadius <= 0)
        { // left boundary
            target->setXCenter(0 + tRadius + 2);
            target->setXVel(-target->getVelocity().x);
        }
        if (tNewPos.y + tRadius >= height)
        { // bottom boundary
            target->setYCenter(height - tRadius - 2);
            target->setYVel(-target->getVelocity().y);
        }
        if (tNewPos.y - tRadius <= 0)
        { // top boundary
            target->setYCenter(0 + tRadius + 2);
            target->setYVel(-target->getVelocity().y);
        }
    }

}