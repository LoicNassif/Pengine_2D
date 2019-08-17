#define CATCH_CONFIG_MAIN
#include "../Engine/interface/config.hpp"

#include <iostream>

/* Vector test cases */
TEST_CASE("Vec2 dot product") {
    Vec2<int> a(0, 1);
    Vec2<int> b(-1, 0);
    Vec2<int> c = a + b;
    REQUIRE(a.x + b.x == c.x);
    REQUIRE(a.y + b.y == c.y);
}

TEST_CASE("Vec2 scalar multiplication")
{
    Vec2<int> a(-1, 1);
    Vec2<int> c = 5*a;
    REQUIRE(5*a.x == c.x);
    REQUIRE(5*a.y == c.y);
}

// int main()
// {
//     Color c = Color::black;
//     double gravity = 0;
//     std::ifstream file("../data/config.json");
//     if (file.is_open()) {
//         json data;
//         file >> data;

//         gravity = data["gravity"];
//         std::string colour = data["colour"];

//         if (colour == "White" || colour == "white") {
//             c = Color::white;
//         }
//     }

//     Engine e;

//     /* Pre start up configurations */
//     // Window config
//     pe::setWindowDimensions(e, 1000, 500);
//     pe::setWindowColor(e, std::move(c));
//     //pe::setDEBUG(e); // paints the centers, also some extra output  

//     // Objects config
//     pe::processJSON(e, "../data/objects.json");

//     /* Engine start up. Initializes all managers. */
//     e.startUp();

//     /* Post start up configurations (e.g. physics settings) */
//     pe::setGravity(e, gravity);

//     std::cout << "engine start-up completed." << std::endl;

//     /* Engine main while-loop. */
//     e.run();

//     /* Engine shut down. Closes all managers in the right order. */
//     e.shutDown();

//     std::cout << "engine shut down completed." << std::endl;

//     return 0;
// }