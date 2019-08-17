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
}