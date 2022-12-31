#include "Visualization.hpp"

void DrawCircle()
{
    sf::RenderWindow window(sf::VideoMode(199, 200), "SFML works!");
    sf::CircleShape shape(99.f);
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
}