#include "headers/physicsManager.hpp"

void PhysicsManager::startUp() {
    
}

void PhysicsManager::update(SDL_Event& e) {

}

void PhysicsManager::shutDown() {

}

bool PhysicsManager::checkCircularCollision(Circle* a, Circle* b) {
    Vec2<double> b_coord = b->getCenter();
    Vec2<double> a_coord = a->getCenter();

    int ub = (b->getRadius() + a->getRadius()) * (b->getRadius() + a->getRadius());
    int lb = (b->getRadius() - a->getRadius()) * (b->getRadius() - a->getRadius());
    double intersec = (b_coord.x - a_coord.x) * (b_coord.x - a_coord.x) + (b_coord.y - a_coord.y) * (b_coord.y - a_coord.y);

    return ((int)intersec < ub);
}

void PhysicsManager::elasticCollision(Circle* a, Circle* b) {
    double m_a = a->getMass();
    double m_b = b->getMass();
    Vec2<double> v_a = a->getVelocity();
    Vec2<double> v_b = b->getVelocity();
    Vec2<double> c_a = a->getCenter();
    Vec2<double> c_b = b->getCenter();

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

void PhysicsManager::wallCircularCollision(Circle* target) {
    int width = engine_ptr->getWindowManager()->getWindowWidth();
    int height = engine_ptr->getWindowManager()->getWindowHeight();
    int tRadius = target->getRadius();
    // Vec2<int> tNewPos = target->getCenter() + target->getVelocity() * m_dt;

    // target->setYVel(target->getVelocity().y + 0.5 * m_gg * m_dt);
    // if (tNewPos.x + tRadius < width && tNewPos.x - tRadius > 0 && tNewPos.y - tRadius > 0 && tNewPos.y + tRadius < height)
    // {
    //     dv = tNewVel - target->getVelocity();
    //     dx.x = (int)(tNewPos.x - target->getCenter().x);
    //     dx.y = (int)(tNewPos.y - target->getCenter().y);
    //     target->setXCenter(tNewPos.x);
    //     target->setYCenter(tNewPos.y);
    //     target->setXVel(tNewVel.x);
    //     target->setYVel(tNewVel.y);
    // }

    if (target->getCenter().x + tRadius >= width)
    { // right boundary
        //target->setXCenter(width - tRadius);
        target->setXVel(-target->getVelocity().x);
    }
    if (target->getCenter().x - tRadius <= 0)
    { // left boundary
        //target->setXCenter(0 + tRadius);
        target->setXVel(-target->getVelocity().x);
    }
    if (target->getCenter().y + tRadius >= height)
    { // bottom boundary
        //target->setYCenter(height - tRadius);
        target->setYVel(-target->getVelocity().y);
    }
    if (target->getCenter().y - tRadius <= 0)
    { // top boundary
        //target->setYCenter(0 + tRadius);
        target->setYVel(-target->getVelocity().y);
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
  
                    // Wall collision (computes new velocities)
                    wallCircularCollision(sCircle);

                    Vec2<double> sNewPos = Vec2<double>(0, 0);
                    Vec2<double> sNewVel = Vec2<double>(0, 0);
                    velocityVerlet(sNewPos, sNewVel, sCircle);
                    sCircle->setCenter(sNewPos);
                    sCircle->setXVel(sNewVel.x);
                    sCircle->setYVel(sNewVel.y);

                    // Wall collision (computes new velocities)
                    wallCircularCollision(target);

                    Vec2<double> tNewPos = Vec2<double>(0, 0);
                    Vec2<double> tNewVel = Vec2<double>(0, 0);
                    velocityVerlet(tNewPos, tNewVel, target);
                    target->setCenter(tNewPos);
                    target->setXVel(tNewVel.x);
                    target->setYVel(tNewVel.y);

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
        // Wall collision (computes new velocities)
        wallCircularCollision(target);

        Vec2<double> tNewPos = Vec2<double>(0, 0);
        Vec2<double> tNewVel = Vec2<double>(0, 0);
        velocityVerlet(tNewPos, tNewVel, target);

        Vec2<double> dv = Vec2<double>(0, 0);
        Vec2<int> dx = Vec2<int>(0, 0);

        // DEBUG computations
        if (engine_ptr->getWindowManager()->getDebugStatus()) {
            dv = tNewVel - target->getVelocity();

            dx.x = (int)(tNewPos.x - target->getCenter().x);
            dx.y = (int)(tNewPos.y - target->getCenter().y);
        }

        target->setXCenter(tNewPos.x);
        target->setYCenter(tNewPos.y);
        target->setXVel(tNewVel.x);
        target->setYVel(tNewVel.y);

        // DEBUG output
        if(engine_ptr->getWindowManager()->getDebugStatus()) {
            std::cout << "velocity: " << target->getVelocity() << "\t dv: " << dv << "\t position: " << target->getCenter() << "\t dx: " << dx << std::endl;
        }
    }
}

void PhysicsManager::velocityVerlet(Vec2<double>& newPos, Vec2<double>& newVel, Circle* a) {
    // Implement half stepping
    double newVXhalf = a->getVelocity().x;
    double newX = a->getCenter().x + m_dt * newVXhalf;
    double newVX = newVXhalf;
    
    double newVYhalf = a->getVelocity().y + 0.5 * m_dt * m_gg;
    double newY = a->getCenter().y + m_dt * newVYhalf;
    double newVY = newVYhalf + 0.5 * m_dt * m_gg;

    newPos.x = newX; newPos.y = newY;
    newVel.x = newVX; newVel.y = newVY;
}