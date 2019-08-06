#include "../Engine/interface/config.hpp"

#include <iostream>

int main()
{
    Engine e;

    /* Pre start up configurations */
    // Window config
    pe::setWindowDimensions(e, 1000, 500);
    pe::setWindowColor(e, Color::black);

    // Objects config
    Circle *c1 = new Circle(Vec2<int>(100, 100), 30, Vec2<int>(3, 0), 1);
    Circle *c2 = new Circle(Vec2<int>(300, 250), 50, Vec2<int>(1, 2), 1);
    Circle *c3 = new Circle(Vec2<int>(600, 300), 95, Vec2<int>(3, -1), 1);
    Circle *c4 = new Circle(Vec2<int>(800, 30), 10, Vec2<int>(-10, 4), 1);

    pe::pushShape(e, c1);
    pe::pushShape(e, c2);
    pe::pushShape(e, c3);
    pe::pushShape(e, c4);

    /* Engine start up. Initializes all managers. */
    e.startUp();

    /* Post start up configurations */
    // TODO

    std::cout << "engine start-up completed." << std::endl;

    /* Engine main while-loop. */
    e.run();

    /* Engine shut down. Closes all managers in the right order. */
    e.shutDown();

    std::cout << "engine shut down completed." << std::endl;

    return 0;
}