#include "../Engine/interface/config.hpp"

#include <iostream>

int main()
{
    Engine e;

    /* Pre start up configurations */
    // Window config
    pe::setWindowDimensions(e, 1000, 500);
    pe::setWindowColor(e, Color::black);
    //pe::setDEBUG(e); // paints the centers  

    // Objects config
    pe::processJSON(e, "../data/objects.json");

    /* Engine start up. Initializes all managers. */
    e.startUp();

    /* Post start up configurations (e.g. physics settings) */
    // TODO

    std::cout << "engine start-up completed." << std::endl;

    /* Engine main while-loop. */
    e.run();

    /* Engine shut down. Closes all managers in the right order. */
    e.shutDown();

    std::cout << "engine shut down completed." << std::endl;

    return 0;
}