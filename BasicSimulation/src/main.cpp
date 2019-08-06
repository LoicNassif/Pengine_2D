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
    Circle *c1 = new Circle(Vec2<int>(100, 100), 30);
    Circle *c2 = new Circle(Vec2<int>(300, 250), 50);

    pe::pushShape(e, c1);
    pe::pushShape(e, c2);

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