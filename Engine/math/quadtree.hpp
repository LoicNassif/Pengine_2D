#pragma once
#include <array>
#include <vector>
#include "../renderer/headers/circle.hpp"

/*
Inspired by the following design tutorial,
https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
*/
class Quadtree {
    public:
        Quadtree(int _lvl, Vec2<int> _init, int _width, int _height) : current_level(_lvl), init_point(_init), width(_width), height(_height) {}
        ~Quadtree() {}

        // Clears the quadtree of all objects and children
        void clear() {
            objects.erase(objects.begin(), objects.end());
        
            for (int i=0; i<children.size(); i++) {
                if (children[i] != nullptr) {
                    children[i]->clear();
                    delete children[i];
                    children[i] = nullptr;
                }
            }
        }

        // Split the node into 4 children
        void split() {
            int sub_width = width / 2;
            int sub_height = height / 2;

            children[0] = new Quadtree(current_level+1, init_point, sub_width, sub_height); // Top-left
            children[1] = new Quadtree(current_level+1, Vec2<int>(init_point.x + sub_width, init_point.y), sub_width, sub_height); // Top-right
            children[2] = new Quadtree(current_level+1, Vec2<int>(init_point.x, init_point.y + sub_height), sub_width, sub_height); // Bottom-left
            children[3] = new Quadtree(current_level+1, Vec2<int>(init_point.x + sub_width, init_point.y + sub_height), sub_width, sub_height); // Bottom-right
        }

        // Find the node for a specific shape
        int getIndex(Shape* target) {
            int index = -1;
            double vMidpoint = init_point.x + (width / 2);
            double hMidpoint = init_point.y + (height / 2);

            // Handle if the shape is a circle
            if (Circle* tCircle = dynamic_cast<Circle*>(target)) {
                double left_bnd = tCircle->getCenter().x - tCircle->getRadius(); // Left boundary
                double right_bnd = tCircle->getCenter().x + tCircle->getRadius(); // Right boundary
                double bottom_bnd = tCircle->getCenter().y + tCircle->getRadius(); // Bottom boundary
                double top_bnd = tCircle->getCenter().y - tCircle->getRadius(); // Top boundary

                // Left half
                if (left_bnd > init_point.x && right_bnd < vMidpoint) {
                    // Top-left quadrant
                    if (top_bnd > init_point.y && bottom_bnd < hMidpoint) {
                        index = 0;
                    }
                    // Bottom-left quadrant
                    else if (top_bnd > hMidpoint && bottom_bnd < height) {
                        index = 2;
                    }
                }

                // Right half
                if (left_bnd > vMidpoint && right_bnd < width) {
                    // Top-right quadrant
                    if (top_bnd > init_point.y && bottom_bnd < hMidpoint) {
                        index = 1;
                    }
                    // Bottom-right quadrant
                    else if (top_bnd > hMidpoint && bottom_bnd < height) {
                        index = 3;
                    }
                }
            }

            return index;
        }

        // Insert a given shape into the tree
        void insert(Shape* target) {
            // Current tree has children so pass down the target to the proper child
            if (children[0] != nullptr) {
                int index = getIndex(target);

                if (index != -1) {
                    children[index]->insert(target);
                    return;
                }
            }

            // Index was -1 or node is leaf, so add the object here
            objects.push_back(target);

            // Check if we have to split the area into children
            if (objects.size() > max_size && current_level < max_depth) {
                if (children[0] != nullptr) {
                    split();
                }
                
                // Redistribute objects to the new trees
                int i=0;
                while (i<objects.size()) {
                    int index = getIndex(objects[i]);
                    if (index != -1) {
                        children[index]->insert(objects[i]);
                        objects.erase(objects.begin() + i);
                    } else {
                        i++;
                    }
                }
            }
        }

        // Retrieve all possible colliding targets for said shape
        void retrieve(std::vector<Shape*>& listTargets, Shape* target) {
            int index = getIndex(target);

            // Look into its children
            if (index != -1 && children[0] != nullptr) {
                children[index]->retrieve(listTargets, target);
            }

            for (int i=0; i<objects.size(); i++) {
                listTargets.push_back(objects[i]);
            }
        }

    private:
        int max_depth = 50;
        int max_size = 5;
        int current_level;
        std::array<Quadtree*, 4> children;
        std::vector<Shape*> objects;
        Vec2<int> init_point;
        int width;
        int height;
};