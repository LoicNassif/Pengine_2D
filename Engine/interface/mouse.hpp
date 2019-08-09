#pragma once
#include <SDL.h>
#undef main

enum class Status { PRESSDOWN, RELEASED, HOLDINGDOWN };

class Mouse {
    public:
        Mouse() { SDL_GetMouseState(&x, &y); }
        ~Mouse(){}

        void updateCurrentMousePos() { SDL_GetMouseState(&x, &y); };
        int getXPos() { return x; }
        int getYPos() { return y; }
        Status getState() { return state; }

        void update(const SDL_Event &e) {

            updateCurrentMousePos();
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (state == Status::PRESSDOWN) {
                    state = Status::HOLDINGDOWN;
                }
                if (state == Status::RELEASED) {
                    state = Status::PRESSDOWN;
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                if (state == Status::PRESSDOWN || state == Status::HOLDINGDOWN) {
                    state = Status::RELEASED;
                }
            }
        }

    private:
        int x;
        int y;
        Status state = Status::RELEASED;
};