#include "../Engine/interface/config.hpp"

#include <iostream>

int main()
{
    Engine e;

    /* Pre start up configurations */
    pe::setWindowDimensions(e, 1000, 500);
    pe::setWindowColor(e, Color::black);

    e.startUp();

    std::cout << "engine start-up completed." << std::endl;

    e.run();

    std::cout << "engine running ended." << std::endl;

    e.shutDown();

    std::cout << "engine shut down completed." << std::endl;

    return 0;
}