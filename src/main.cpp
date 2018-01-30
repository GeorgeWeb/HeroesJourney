#include <Engine/SFMLGraphics.hpp>
#include <Engine/SM/StateMachine.hpp>

#include <iostream>

using namespace Engine;

auto main(void) -> int
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;

    return EXIT_SUCCESS;
}