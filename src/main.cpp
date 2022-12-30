#include "main.hpp"
#include "Algorithm.hpp"
#include "SFML/Graphics.hpp"

void DrawCircle()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
}
int main(){
    int array[10] = {6,4,2,18,8,1,33,12,7,0};
    //Sort<int>::Insertion(array, array + 10);
    //Sort<int>::Selection(array, array + 10);
    Sort<int>::Bubble(array, array + 10);
    Sort<int>::print(array, array + 10);
    //DrawCircle();
    return 0;
}