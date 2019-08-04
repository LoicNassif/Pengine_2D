#include "headers/engine.hpp"
#include "headers/windowManager.hpp"
#include <iostream>

WindowManager gWindowManager;

void Engine::startUp() {
    gWindowManager.startUp();
    
    std::cout << "\t window manager start up complete." << std::endl;
}

void Engine::run() {
    SDL_Event e;
    bool shutDownFlag = false;

    // main loop
    std::cout << "\t engine running" << std::endl;
    while(!shutDownFlag) {
        gWindowManager.update(e);
        gWindowManager.render();
        if (!gWindowManager.getStatus()) { shutDownFlag = true; }
    }
}

void Engine::shutDown() {
    gWindowManager.shutDown();

    std::cout << "\t window manager shut down complete." << std::endl;
}
