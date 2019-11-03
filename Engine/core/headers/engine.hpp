#pragma once
#include <SDL.h>
#undef main
#include <memory>

#include "windowManager.hpp"
#include "physicsManager.hpp"
#include "textureManager.hpp"
#include "../../utils/timer.hpp"

class WindowManager;
class PhysicsManager;
class TextureManager;

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
        inline WindowManager *getWindowManager() const { return mWindowManager.get(); } 
        inline PhysicsManager *getPhysicsManager() const { return mPhysicsManager.get(); }
        inline TextureManager *getTextureManager() const { return mTextureManager.get(); }

    private:
        std::unique_ptr<WindowManager> mWindowManager;
        std::unique_ptr<PhysicsManager> mPhysicsManager;
        std::unique_ptr<TextureManager> mTextureManager;

        // FPS timer
        Timer FPStimer;

        // FPS string
        std::string FPStext = "";
};