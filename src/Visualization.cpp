#include "Visualization.hpp"

const float PILLAR_WIDTH = 10.f; 
const float PILLAR_HEIGHT = 6.f;
const int PILLAR_SIZE = 100;  


void visualizeSorting()
{

    sf::RenderWindow window(sf::VideoMode(1250, 850), "Algorithm Visualization");
    window.setFramerateLimit(60);
    //setup the sorted array
    std::array<int, PILLAR_SIZE> arr; 
    for(int i = 0; i < PILLAR_SIZE; i++)
    {
        arr[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 prng(rd());
    std::shuffle(arr.begin(), arr.end(), prng);

    int pillars_value[PILLAR_SIZE] = {0};

    for(int i = 0; i < PILLAR_SIZE; i++)
    {
        pillars_value[i] = arr[i];
        std::cout << pillars_value[i] << " ";
    }

    //setup Font and sort info
    sf::Font SortFont;
    if(!SortFont.loadFromFile("res/Sugar Snow.ttf"))
    {
        std::cout<<"Load Font Fail!!"<<std::endl;
    }

    sf::Text accessCount("Array access: ", SortFont, 20);
    accessCount.setStyle(sf::Text::Regular);
    accessCount.setPosition(100, 50);
    
    //setup the pillars
    std::array<sf::RectangleShape, PILLAR_SIZE> pillars;
    for(unsigned int i = 0; i < pillars.size(); i++)
    {
        pillars[i].setFillColor(sf::Color::White);
        pillars[i].setOutlineColor(sf::Color::Black);
        pillars[i].setOutlineThickness(2.f);
    }
    
    auto Visualize = [&window, &pillars](int* start)
    {
        if(window.isOpen())
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            
            for(unsigned int i = 0; i < pillars.size(); i++)
            {
                pillars[i].setSize(sf::Vector2f(PILLAR_WIDTH, - PILLAR_HEIGHT * (*(start + i))));
                pillars[i].setPosition(30 + (PILLAR_WIDTH + 2) * i , 800.f); //plus 2 pixel for the outline of the rectangle
                window.draw(pillars[i]);
            }
            
            //window.draw(accessCount);

            window.display();
        }
    };

    //Insertion(pillars_value, pillars_value + PILLAR_SIZE, Visualize);
    //Selection(pillars_value, pillars_value + PILLAR_SIZE, Visualize);
    Bubble(pillars_value, pillars_value + PILLAR_SIZE, Visualize);
}

void Insertion(int* start, int* end, std::function<void (int*)> visualize)
{
    int size = end - start;
    for(int i = 1; i < size; i++)
    {
        int temp = *(start + i);
        int j = i;
        while(temp < *(start + j - 1) && j - 1 >= 0)
        {
            *(start + j) = *(start + j - 1);
            j--;
            visualize(start);
        }
        *(start + j) = temp;
    }
}

void Selection(int* start, int* end, std::function<void (int*)> visualize)
{
   int size = end - start;
   for(int i = 0; i < size - 1; i++)
   {
      int min = *(start + i);
      int min_idx = i;
      for(int j = i + 1; j < size; j++)
      {
         if(*(start + j) < min)
         {
            min = *(start + j);
            min_idx = j;
         }
      }
      int temp = *(start + i);
      *(start + i) = *(start + min_idx);
      *(start + min_idx) = temp;
      visualize(start);
   }
}

void Bubble(int* start, int* end, std::function<void (int*)> visualize)
{
   bool sorted = true;
   int size = end - start;
    for(int i = 0; i < size - 1; i++)
    {
        sorted = true;
        for(int j = size - 1; j > i; j--)
        {
            if(*(start + j) < *(start + j - 1))
            {
            sorted = false;
            int temp = *(start + j);
            *(start + j) = *(start + j - 1);
            *(start + j - 1) = temp;
            }
            visualize(start);
        }
        if(sorted) break;
    }
}
