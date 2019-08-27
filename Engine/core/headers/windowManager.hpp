#pragma once
#include <SDL.h>
#undef main
#include <vector>
#include "../../renderer/headers/shape.hpp"
#include "../../utils/mouse.hpp"
#include "../../math/quadtree.hpp"
#include "engine.hpp"

enum class Color { white, black };

class Engine;

class WindowManager
{
public:
    WindowManager(const Engine* e) : engine_ptr(e) {};
    ~WindowManager(){};

    // Window manager start-up
    void startUp();

    // Window manager shut-down
    void shutDown();

    // Render functions
    void render();
    void update(SDL_Event &e);
    void updatePaused(const SDL_Event& e);

    // Getters
    inline bool getStatus() { return mStatus; }
    inline int getWindowWidth() { return mWidth; }
    inline int getWindowHeight() { return mHeight; }
    bool getDebugStatus() { return mDebug; }
    inline SDL_Renderer* getRenderer() { return mRenderer; }
    bool getFPSflag() { return displayFPS; }

    // Setters
    inline void setWindowWidth(int w) { mWidth = w; }
    inline void setWindowHeight(int h) { mHeight = h; }
    inline void setWindowColor(Color&& c) { mColor = c; }
    inline void setDebugMode(bool flag) { mDebug = flag; }
    inline void disableQuadTreeOpt() { quadtreeOpt = false; }

private :
    // FPS display flag
    bool displayFPS = true;

    // quadtree flag
    bool quadtreeOpt = true;

    // Hold a quadtree for collision detection
    Quadtree* collTree;

    // log on previous mouse position
    Vec2<double> prevMousePos = Vec2<double>(0,0);

    // Paused
    bool isPaused = false;

    // A mouse object
    Mouse mouse;

    // Currently selected shape
    Shape *shape_ptr = nullptr;

    // Debug mode flag
    bool mDebug = false;

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

    // Instance of the engine
    const Engine *engine_ptr = nullptr;
};