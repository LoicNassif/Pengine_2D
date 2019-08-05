#pragma once
#include <SDL.h>
#undef main

#include "windowManager.hpp"

class Engine {
    public:
        Engine();
        ~Engine() {};

        // Do not allow copy semantics
        Engine(const Engine&) = delete;
        void operator=(const Engine&) = delete;

        // Engine Start-up
        void startUp();

        // Engine Shut-down
        void shutDown();

        // Engine run
        void run();

        // Getters
        inline WindowManager* getWindowManager() const { return mWindowManager; } 

    private:
        WindowManager *mWindowManager;
};