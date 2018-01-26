#include <SFML/Graphics.hpp>
#include <iostream>

auto main(void) -> int
{
    sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }

    return EXIT_SUCCESS;
}