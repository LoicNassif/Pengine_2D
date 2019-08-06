#include "headers/windowManager.hpp"
#include <iostream>

void WindowManager::startUp() {
    initWindow("Pengine", mWidth, mHeight, true);
    createRenderer();
}

void WindowManager::shutDown() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = NULL;
    mRenderer = NULL;
}

void WindowManager::render() {
    // Clear screen
    SDL_RenderClear(mRenderer);

    if (mColor == Color::black) {
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
    }

    /* Render all objects */
    for (Shape *s : objects) {
        s->render(*mRenderer);
    }

    if (mColor == Color::black)
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
    else
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderPresent(mRenderer);
}

void WindowManager::update(SDL_Event& e) {
    while (SDL_PollEvent(&e) != 0) {
        handleEvent(e);
    }

    /* Update all objects */
    for (Shape *s : objects) {
        s->move(s->getVelocity(), mWidth, mHeight, objects);
    }
}

void WindowManager::handleEvent(const SDL_Event& e) {
    // Window event occured
    if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
    {
        // Caption update flag
        bool updateCaption = false;
        switch (e.window.event)
        {
        // Get new dimensions and repaint on window size change
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            SDL_RenderPresent(mRenderer);
            break;

        // Repaint on exposure
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(mRenderer);
            break;

        // Mouse entered window
        case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            updateCaption = true;
            break;

        // Mouse left window
        case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            updateCaption = true;
            break;

        // Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            updateCaption = true;
            break;

        // Window lost keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            updateCaption = true;
            break;

        // Hide and close program on close
        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow(mWindow);
            mStatus = false;
            break;
        }
    }
}

bool WindowManager::initWindow(const char *title, int screen_width, int screen_height, bool shown) {
    // Create Window
    mWindow = SDL_CreateWindow("Pengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, 
                                screen_height, SDL_WINDOW_SHOWN);

    // Grab window indentifier
    mWindowID = SDL_GetWindowID(mWindow);

    // TODO: error checking
    return true;
}

bool WindowManager::createRenderer() {
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // TODO: error checking
    return true;
}