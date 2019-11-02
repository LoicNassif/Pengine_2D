#include "headers/engine.hpp"
#include <iostream>
#include <string>

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

    if (mWindowManager->getFPSflag()) {
        FPStimer.start();
    }
}

void Engine::run() {
    SDL_Event e;
    bool shutDownFlag = false;
    int countedFrames = 0;

    // TTF_Font* f = TTF_OpenFont("../fonts/Oswald-Light.ttf", 18);
    // if (f == nullptr) {
        // std::cout << "Could not load font\n";
    // }

    SDL_Color colour = {255, 255, 255};

    // main loop
    std::cout << "\t engine running" << std::endl;
    while(!shutDownFlag) {
        if (mWindowManager->getFPSflag()) {
            double avgFPS = countedFrames / (FPStimer.getTicks() / 1000.f);
            if (avgFPS > 2000000) avgFPS = 0;
            mTextureManager->clearTexture(FPStext);
            FPStext = std::to_string(avgFPS);
            // mTextureManager->loadRenderedText(FPStext, colour, f, 5, 2);
        }

        mWindowManager->update(e);
        mWindowManager->render();
        if (!mWindowManager->getStatus()) { shutDownFlag = true; }
        countedFrames++;
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