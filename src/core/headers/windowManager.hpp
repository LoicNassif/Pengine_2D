#pragma once
#include <SDL.h>
#undef main

class WindowManager {
    public:
        WindowManager() {};
        ~WindowManager() {};

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
        int mWidth;
        int mHeight;

        // Window focii
        bool mMouseFocus;
        bool mKeyboardFocus;
};