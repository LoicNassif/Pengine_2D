#include "headers/engine.hpp"
#include <iostream>

Engine::Engine() {
    // Create Managers
    mWindowManager = new WindowManager();
}

void Engine::startUp() {
    // Start up the managers
    mWindowManager->startUp();
    std::cout << "\t window manager start up complete." << std::endl;
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

    std::cout << "\t window manager shut down complete." << std::endl;
}