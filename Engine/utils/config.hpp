#pragma once
#include "../core/headers/engine.hpp"
#include "../renderer/headers/circle.hpp"
#include <nlohmann/json.hpp>
#include <utility>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace pe {
    void setWindowDimensions(const Engine &e, int w, int h) {
        e.getWindowManager()->setWindowHeight(h);
        e.getWindowManager()->setWindowWidth(w);
    }

    void setWindowColor(const Engine &e, Color&& c) {
        e.getWindowManager()->setWindowColor(std::move(c));
    }

    void setGravity(const Engine &e, double g) {
        e.getPhysicsManager()->setGravity(g);
    }

    void setUniformDrag(const Engine &e, double d) {
        e.getPhysicsManager()->setUniformDrag(d);
    }

    void pushShape(const Engine &e, Shape* s) {
        e.getPhysicsManager()->objects.push_back(s);
    }

    void processJSON(const Engine &e, const std::string&& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            json data;
            file >> data;

            json objs = data["objects"];

            for (json& obj : objs) {
                std::string shape_type = obj["shape"];
                int size = obj["size"];
                int x_pos = obj["x_pos"];
                int y_pos = obj["y_pos"];
                int x_vel = obj["x_vel"];
                int y_vel = obj["y_vel"];
                int mass = obj["mass"];

                if (shape_type == "Circle" || shape_type == "circle") {
                    Circle *c = new Circle(Vec2<double>(x_pos, y_pos), size, Vec2<double>(x_vel, y_vel), mass);
                    pushShape(e, c);
                }
            }
        }
    }

    void setDEBUG(const Engine &e) {
        e.getWindowManager()->setDebugMode(true);
    }

    void disableQuadTreeOpt(const Engine &e) {
        e.getWindowManager()->disableQuadTreeOpt();
    } 

    void addText(const Engine &e, std::string text, Color c, std::string font, int size, int posx, int posy) {
        SDL_Color colour = {255, 255, 255};
        switch(c) {
            case Color::black:
                colour.b = 0;
                colour.g = 0;
                colour.r = 0;
                break;
            case Color::white:
                break;
        }
        TTF_Font* f = TTF_OpenFont(font.c_str(), size);
        if (f == nullptr) {
            std::cout << "Could not load font\n";
        }
        if (e.getTextureManager()->loadRenderedText(text, colour, f, posx, posy)) {
            std::cout << "Success loading text: " << font << "\n";
        }
    }

    void displayFPS(const Engine &e) {
        e.getWindowManager()->setDisplayFPS();
    }
}