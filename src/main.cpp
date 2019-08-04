#include "core/headers/engine.hpp"
#include <iostream>

int main()
{
    Engine e;

    e.startUp();

    std::cout << "engine start-up completed." << std::endl;

    e.run();

    std::cout << "engine running ended." << std::endl;

    e.shutDown();

    std::cout << "engine shut down completed." << std::endl;

    return 0;
}