#include "headers/engine.hpp"
#include <iostream>

Engine::Engine() {
    // Create Managers
    mWindowManager = std::unique_ptr<WindowManager>(new WindowManager(this));
    mPhysicsManager = std::unique_ptr<PhysicsManager>(new PhysicsManager(this));
    mTextureManager = std::unique_ptr<TextureManager>(new TextureManager(this));
}

void Engine::startUp() {
    // Start up the managers
    mWindowManager->startUp();
    std::cout << "\t window manager start up complete.\n";
    
    mPhysicsManager->startUp();
    std::cout << "\t physics manager start up complete.\n";

    mTextureManager->startUp();
    std::cout << "\t texture manager start up complete.\n";
}

void Engine::run() {
    SDL_Event e;
    bool shutDownFlag = false;
    
    // main loop
    std::cout << "\t engine running" << std::endl;
    while(!shutDownFlag) {
        mWindowManager->update(e);
        mWindowManager->render();
        if (!mWindowManager->getStatus()) { shutDownFlag = true; }
    }
}

void Engine::shutDown() {
    mWindowManager->shutDown();
    std::cout << "\t window manager shut down complete.\n";

    mPhysicsManager->shutDown();
    std::cout << "\t physics manager shut down complete.\n";

    mTextureManager->shutDown();
    std::cout << "\t texture manager shut down complete.\n";
}