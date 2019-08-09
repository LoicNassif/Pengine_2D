#pragma once
#include <vector>
#include "../../renderer/headers/shape.hpp"

class Engine;

class PhysicsManager {
    public:
        PhysicsManager(const Engine* e) : engine_ptr(e) {}
        ~PhysicsManager(){}

        // Physics manager start-up
        void startUp();

        // Physics manager shut-down
        void shutDown();

        // Update and handle events
        void update(SDL_Event& e);
        void handleEvent(const SDL_Event& e);

        // Physics functions
        bool checkCircularCollision(int x1, int y1, int x2, int y2, int r) {
            return std::abs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < (r * r);
        }

        // Object list
        std::vector<Shape *> objects;

    private:
        // Engine instance
        const Engine* engine_ptr = nullptr;
};