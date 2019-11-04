#include "headers/physicsManager.hpp"
#include <cmath>

void PhysicsManager::startUp() {
    
}

void PhysicsManager::update(SDL_Event& e) {

}

void PhysicsManager::shutDown() {

}

bool PhysicsManager::checkCircleLineCollision(Circle *c, Vec2<double> p1, Vec2<double> p2) {
    double q = c->getPosition().y;
    double p = c->getPosition().x;

    double lineX1 = p2.x - p1.x;
    double lineY1 = p2.y - p1.y;
    double lineX2 = p - p1.x;
    double lineY2 = q - p1.y;

    double lineLength = lineX1 * lineX1 + lineY1 * lineY1;

    double t = std::max((const double)0, std::min(lineLength, (lineX1*lineX2 + lineY1*lineY2))) / lineLength;
    
    Vec2<double> closestPoint = Vec2<double>(p1.x + t*lineX1, p1.y + t*lineY1);
    
    double distance = std::sqrt((p - closestPoint.x) * (p - closestPoint.x) + (q - closestPoint.y)*(q - closestPoint.y));

    return (distance <= (c->getRadius()));
}

bool checkCenterCircleInRectangle(Circle *c, Rectangle* r) {
    bool x = r->getPosition().x <= c->getPosition().x <= r->getPosition().x + r->getWidth();
    bool y = r->getPosition().y <= c->getPosition().y <= r->getPosition().y + r->getHeight();
    return (x && y);
}

bool PhysicsManager::checkCircleRectangleCollision(Circle *c, Rectangle* r) {
    bool top = checkCircleLineCollision(c, r->getPosition(), r->getPosition() + Vec2<double>(r->getWidth(), 0));

    bool left = checkCircleLineCollision(c, r->getPosition(), r->getPosition() + Vec2<double>(0, r->getHeight()));

    bool bottom = checkCircleLineCollision(c, r->getPosition() + Vec2<double>(0, r->getHeight()), r->getPosition() + Vec2<double>(r->getWidth(), r->getHeight()));

    bool right = checkCircleLineCollision(c, r->getPosition() + Vec2<double>(r->getWidth(), 0), r->getPosition() + Vec2<double>(r->getWidth(), r->getHeight()));

    bool center = checkCenterCircleInRectangle(c, r);
    if (top) {
        c->setYPos(r->getPosition().y - c->getRadius());
        c->setYVel(-c->getVelocity().y);
    }
    if (right) {
        c->setXPos(r->getPosition().x + r->getWidth() + c->getRadius());
        if (!top && !bottom) c->setXVel(-c->getVelocity().x);
    }
    if (left) {
        c->setXPos(r->getPosition().x - c->getRadius());
        if (!top && !bottom) c->setXVel(-c->getVelocity().x);
    }
    if (bottom) {
        c->setYPos(r->getPosition().y + r->getHeight() + c->getRadius());
        c->setYVel(-c->getVelocity().y);
    }
}

bool PhysicsManager::checkCircularCollision(Circle* a, Circle* b) {
    Vec2<double> b_coord = b->getPosition();
    Vec2<double> a_coord = a->getPosition();

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
    Vec2<double> c_a = a->getPosition();
    Vec2<double> c_b = b->getPosition();

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

    // clip the velocities if too low
    if (a->getVelocity().x < 0.1 && a->getVelocity().x > -0.1)
    {
        a->setXVel(0);
    }
    if (a->getVelocity().y < 0.1 && a->getVelocity().y > -0.1)
    {
        a->setYVel(0);
    }

    if (b->getVelocity().x < 0.1 && b->getVelocity().x > -0.1)
    {
        b->setXVel(0);
    }
    if (b->getVelocity().y < 0.1 && b->getVelocity().y > -0.1)
    {
        b->setYVel(0);
    }
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

    if (target->getPosition().x + tRadius >= width)
    { // right boundary
        target->setXPos(width - tRadius);
        if (target->getVelocity().x < 0.05 && target->getVelocity().x > -0.05) {
            target->setXVel(0);
        } else {
            target->setXVel(-target->getVelocity().x);
        }
    }
    if (target->getPosition().x - tRadius <= 0)
    { // left boundary
        target->setXPos(0 + tRadius);
        if (target->getVelocity().x < 0.05 && target->getVelocity().x > -0.05) {
            target->setXVel(0);
        } else {
            target->setXVel(-target->getVelocity().x);
        }
    }
    if (target->getPosition().y + tRadius >= height)
    { // bottom boundary
        target->setYPos(height - tRadius);
        if (m_gg > 0) {
            if (target->getVelocity().y < 2.7 && target->getVelocity().y > -2.7) {
                // Add ultra drag
                target->setYVel(-target->getVelocity().y * 0.7);
            if (target->getVelocity().y < 0.47 && target->getVelocity().y > -0.47) {
                target->setYVel(0);
            }
            } else {
                target->setYVel(-target->getVelocity().y);
            }
        } else {
            target->setYVel(-target->getVelocity().y);
        }
    }
    if (target->getPosition().y - tRadius <= 0)
    { // top boundary
        target->setYPos(0 + tRadius);
        if (target->getVelocity().y < 0.05 && target->getVelocity().y > -0.05) {
            target->setYVel(0);
        } else {
            target->setYVel(-target->getVelocity().y);
        }
    }

    /*
    // bottom boundary
    double lineX1 = (double)width - 0.0;
    double lineY1 = (double)height - (double)height;

    double lineX2 = target->getPosition().x - 0.0;
    double lineY2 = target->getPosition().y - (double)height;

    double edgeLength = lineX1 * lineX1 + lineY1 * lineY1;

    double t = (lineX1 * lineX2 + lineY1 * lineY2) / edgeLength;

    double closestPointX = 0.0 + t * lineX1;
    double closestPointY = (double)height + t * lineY1 + 5;

    staticWallCollision(target, closestPointX, closestPointY);

    // top boundary
    lineX1 = (double)width - 0.0;
    lineY1 = 0.0 - 0.0;

    lineX2 = target->getPosition().x - 0.0;
    lineY2 = target->getPosition().y - 0.0;

    edgeLength = lineX1 * lineX1 + lineY1 * lineY1;

    t = (lineX1 * lineX2 + lineY1 * lineY2) / edgeLength;

    closestPointX = 0.0 + t * lineX1;
    closestPointY = 0.0 + t * lineY1 + 5;

    staticWallCollision(target, closestPointX, closestPointY);

    // left boundary
    lineX1 = 0.0 - 0.0;
    lineY1 = (double)height - 0.0;

    lineX2 = target->getPosition().x - 0.0;
    lineY2 = target->getPosition().y - 0.0;

    edgeLength = lineX1 * lineX1 + lineY1 * lineY1;

    t = (lineX1 * lineX2 + lineY1 * lineY2) / edgeLength;

    closestPointX = 0.0 + t * lineX1;
    closestPointY = 0.0 + t * lineY1 + 5;

    staticWallCollision(target, closestPointX, closestPointY);

    // right boundary
    lineX1 = (double)width - (double)width;
    lineY1 = (double)height - 0.0;

    lineX2 = target->getPosition().x - (double)width;
    lineY2 = target->getPosition().y - 0.0;

    edgeLength = lineX1 * lineX1 + lineY1 * lineY1;

    t = (lineX1 * lineX2 + lineY1 * lineY2) / edgeLength;

    closestPointX = (double)width + t * lineX1;
    closestPointY = 0.0 + t * lineY1 + 5;

    staticWallCollision(target, closestPointX, closestPointY);
*/
}

void PhysicsManager::moveObject(Circle* target, const std::vector<Shape*>& targets) {
    bool haveICollided = false;
    int width = engine_ptr->getWindowManager()->getWindowWidth();
    int height = engine_ptr->getWindowManager()->getWindowHeight();
    int tRadius = target->getRadius();
    /* Check object contraints */
    for (Shape *s : targets)
    {
        if (target != s)
        {
            if (Circle *sCircle = dynamic_cast<Circle *>(s))
            { // Circle-Circle collision
                if (checkCircularCollision(target, sCircle))
                {
                    haveICollided = true;
                    int sRadius = sCircle->getRadius();

                    // Elastic collision (computes new velocities)
                    elasticCollision(target, sCircle);

                    // Wall collision (computes new velocities)
                    wallCircularCollision(sCircle);

                    Vec2<double> sNewPos = Vec2<double>(0, 0);
                    Vec2<double> sNewVel = Vec2<double>(0, 0);
                    velocityVerlet(sNewPos, sNewVel, sCircle);
                    sCircle->setPos(sNewPos);
                    sCircle->setXVel(sNewVel.x);
                    sCircle->setYVel(sNewVel.y);

                    // Wall collision (computes new velocities)
                    wallCircularCollision(target);

                    Vec2<double> tNewPos = Vec2<double>(0, 0);
                    Vec2<double> tNewVel = Vec2<double>(0, 0);
                    velocityVerlet(tNewPos, tNewVel, target);
                    target->setPos(tNewPos);
                    target->setXVel(tNewVel.x);
                    target->setYVel(tNewVel.y);

                    // Static collision resolution
                    if (checkCircularCollision(target, sCircle))
                    {
                        double distance = std::sqrt((sCircle->getPosition().x - target->getPosition().x) * (sCircle->getPosition().x - target->getPosition().x) + (sCircle->getPosition().y - target->getPosition().y) * (sCircle->getPosition().y - target->getPosition().y));
                        double overlap = 0.5 * (distance - tRadius - sRadius);

                        // Displace target circle
                        target->setXPos(target->getPosition().x - overlap * (target->getPosition().x - sCircle->getPosition().x) / distance);
                        target->setYPos(target->getPosition().y - overlap * (target->getPosition().y - sCircle->getPosition().y) / distance);

                        // Displace other circle
                        sCircle->setXPos(sCircle->getPosition().x + overlap * (target->getPosition().x - sCircle->getPosition().x) / distance);
                        sCircle->setYPos(sCircle->getPosition().y + overlap * (target->getPosition().y - sCircle->getPosition().y) / distance);
                    }
                }
            }

            if (Rectangle *sRec = dynamic_cast<Rectangle *>(s)) {
                // Check Rectangle-Circle collision using static collision resolution
                checkCircleRectangleCollision(target, sRec);
            }
        }
    }

    /* Check boundary contraints only if there was no collision */
    if (!haveICollided)
    {
        // Wall collision (computes new velocities)
        wallCircularCollision(target);

        Vec2<double> tNewPos = Vec2<double>(0, 0);
        Vec2<double> tNewVel = Vec2<double>(0, 0);
        velocityVerlet(tNewPos, tNewVel, target);

        Vec2<double> dv = Vec2<double>(0, 0);
        Vec2<int> dx = Vec2<int>(0, 0);

        // DEBUG computations
        if (engine_ptr->getWindowManager()->getDebugStatus())
        {
            dv = tNewVel - target->getVelocity();

            dx.x = (int)(tNewPos.x - target->getPosition().x);
            dx.y = (int)(tNewPos.y - target->getPosition().y);
        }

        target->setXPos(tNewPos.x);
        target->setYPos(tNewPos.y);
        target->setXVel(tNewVel.x);
        target->setYVel(tNewVel.y);

        // DEBUG output
        if (engine_ptr->getWindowManager()->getDebugStatus())
        {
            std::cout << "velocity: " << target->getVelocity() << "\t dv: " << dv << "\t position: " << target->getPosition() << "\t dx: " << dx << std::endl;
        }
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
                    sCircle->setPos(sNewPos);
                    sCircle->setXVel(sNewVel.x);
                    sCircle->setYVel(sNewVel.y);

                    // Wall collision (computes new velocities)
                    wallCircularCollision(target);

                    Vec2<double> tNewPos = Vec2<double>(0, 0);
                    Vec2<double> tNewVel = Vec2<double>(0, 0);
                    velocityVerlet(tNewPos, tNewVel, target);
                    target->setPos(tNewPos);
                    target->setXVel(tNewVel.x);
                    target->setYVel(tNewVel.y);

                    // Static collision resolution
                    if (checkCircularCollision(target, sCircle)) {
                        double distance = std::sqrt((sCircle->getPosition().x - target->getPosition().x) * (sCircle->getPosition().x - target->getPosition().x)
                                                    + (sCircle->getPosition().y - target->getPosition().y) * (sCircle->getPosition().y - target->getPosition().y));
                        double overlap = 0.5 * (distance - tRadius - sRadius);

                        // Displace target circle
                        target->setXPos(target->getPosition().x - overlap * (target->getPosition().x - sCircle->getPosition().x) / distance);
                        target->setYPos(target->getPosition().y - overlap * (target->getPosition().y - sCircle->getPosition().y) / distance);

                        // Displace other circle
                        sCircle->setXPos(sCircle->getPosition().x + overlap * (target->getPosition().x - sCircle->getPosition().x) / distance);
                        sCircle->setYPos(sCircle->getPosition().y + overlap * (target->getPosition().y - sCircle->getPosition().y) / distance);
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

            dx.x = (int)(tNewPos.x - target->getPosition().x);
            dx.y = (int)(tNewPos.y - target->getPosition().y);
        }

        target->setXPos(tNewPos.x);
        target->setYPos(tNewPos.y);
        target->setXVel(tNewVel.x);
        target->setYVel(tNewVel.y);

        // DEBUG output
        if(engine_ptr->getWindowManager()->getDebugStatus()) {
            std::cout << "velocity: " << target->getVelocity() << "\t dv: " << dv << "\t position: " << target->getPosition() << "\t dx: " << dx << std::endl;
        }
    }
}

void PhysicsManager::velocityVerlet(Vec2<double>& newPos, Vec2<double>& newVel, Circle* a) {
    // Implement half stepping
    double newVXhalf = a->getVelocity().x;
    double newX = a->getPosition().x + m_dt * newVXhalf;
    double newVX = (1 - m_uni_drag) * newVXhalf;
    
    double newVYhalf = a->getVelocity().y + 0.5 * m_dt * m_gg;
    double newY = a->getPosition().y + m_dt * newVYhalf;
    double newVY = (1 - m_uni_drag) * (newVYhalf + 0.5 * m_dt * m_gg);

    if (m_gg > 0) {
        if (newVX < 0.1 && newVX > -0.1) {
            newVX = 0;
        }
        
        if (newVY < 0.13 && newVY > -0.13)
        {
            newVY = 0;
        }
        else if (newVY < 0.35 && newVY > -0.35) {
            // super drag
            newVY = 0.6 * newVY;
        }
    }

    newPos.x = newX; newPos.y = newY;
    newVel.x = newVX; newVel.y = newVY;
}