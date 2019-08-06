#pragma once
#include "../core/headers/engine.hpp"
#include "../renderer/headers/circle.hpp"
#include <utility>

namespace pe {
    void setWindowDimensions(const Engine &e, int w, int h) {
        e.getWindowManager()->setWindowHeight(h);
        e.getWindowManager()->setWindowWidth(w);
    }

    void setWindowColor(const Engine &e, Color&& c) {
        e.getWindowManager()->setWindowColor(std::move(c));
    }

    void pushShape(const Engine &e, Shape* s) {
        e.getWindowManager()->objects.push_back(s);
    }
}