#pragma once
#include <SDL.h>
#undef main
#include <vector>
#include "../../renderer/headers/shape.hpp"

enum class Color { white, black };

class WindowManager
{
public:
    WindowManager(){};
    ~WindowManager(){};

    // Window manager start-up
    void startUp();

    // Window manager shut-down
    void shutDown();

    // Render functions
    void render();
    void update(SDL_Event &e);

    // Getters
    inline bool getStatus() { return mStatus; }
    inline int getWindowWidth() { return mWidth; }
    inline int getWindowHeight() { return mHeight; }
    inline SDL_Renderer* getRenderer() { return mRenderer; }

    // Setters
    inline void setWindowWidth(int w) { mWidth = w; }
    inline void setWindowHeight(int h) { mHeight = h; }
    inline void setWindowColor(Color&& c) { mColor = c; }

    // Object list
    std::vector<Shape *> objects;

private:
    // shut down flag
    bool mStatus = true;

    // Handle window events
    void handleEvent(const SDL_Event &e);

    // Create the window
    bool initWindow(const char *title, int screen_width, int screen_height, bool shown);

    // Create renderer
    bool createRenderer();

    // Focus on window
    void focus();

    // Window focii
    inline bool hasMouseFocus();
    inline bool hasKeyboardFocus();

    // Window Data
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mWindowID;

    // Window dimensions
    int mWidth = 300;
    int mHeight = 300;
    Color mColor = Color::white;

    // Window focii
    bool mMouseFocus;
    bool mKeyboardFocus;
};