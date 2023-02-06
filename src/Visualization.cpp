#include "Visualization.hpp"

const float PILLAR_WIDTH = 10.f; 
const float PILLAR_HEIGHT = 6.f;
const int PILLAR_SIZE = 100;  
const int FRAME_RATE = 100;

static inline sf::Font ConfigFont();
static inline void SetSortNameText(sf::Text& sorttype, SortType type);
static inline void RandomizePillarVal(int* pillars_value);
static inline void ConfigSound(sf::Sound& sound, sf::SoundBuffer& buffer, const std::string& src);

static inline void ConfigSound(sf::Sound& sound, sf::SoundBuffer& buffer, const std::string& src)
{
    if(!buffer.loadFromFile(src))
        std::cout<<"fail to load sound source"<<std::endl;
        
    int sampleCount = buffer.getSampleCount();
    const int16_t *sampleArr = new int16_t[sampleCount];
    sampleArr = buffer.getSamples();

    for(int i = 0; i < sampleCount; i++)
    {
        std::cout<<sampleArr[i]<<" ";
    }

    sound.setBuffer(buffer);
    sound.setVolume(50);
    //sound.setPitch(0.01);
    //sound.play();

    std::cout<<"Sample rate: "<< buffer.getSampleRate()<<std::endl;
}

void VisualizeSorting(SortType type)
{
    sf::Sound sound;
    sf::SoundBuffer buffer;
    std::string src = "res/goofy-ahh.wav";
    ConfigSound(sound, buffer, src);

    long int compareCount = 0;
    long int writeArrayCount = 0;
    sf::RenderWindow window(sf::VideoMode(1250, 850), "algorithm visualization");
    window.setFramerateLimit(FRAME_RATE);

    //setup font and sort info
    sf::Font sortFont = ConfigFont();
    
    sf::Text sortNameText("default", sortFont, 15);
    SetSortNameText(sortNameText, type);

    //random array values
    int pillars_value[PILLAR_SIZE] = {0};
    RandomizePillarVal(pillars_value);

    //sort<int>::mergerec(pillars_value, pillars_value + pillar_size);
    //sort<int>::print(pillars_value, pillars_value + pillar_size);
    
    //setup the pillars
    std::array<sf::RectangleShape, PILLAR_SIZE> pillars;
    for(unsigned int i = 0; i < pillars.size(); i++)
    {
        pillars[i].setFillColor(sf::Color::White);
        pillars[i].setOutlineColor(sf::Color::Black);
        pillars[i].setOutlineThickness(2.f);
    }

    auto compareTextVisual = [&compareCount, &sortFont]() -> sf::Text
    { 
        
        sf::Text compareCountNum("data reading and comparing count: " + std::to_string(compareCount), sortFont, 15);
        compareCountNum.setPosition(100, 50); 
        return compareCountNum;
    };
    
    auto writeTextVisual = [&writeArrayCount, &sortFont]() -> sf::Text
    { 
        sf::Text writeCountNum("data writing count: " + std::to_string(writeArrayCount), sortFont, 15);
        writeCountNum.setPosition(100, 78); 
        return writeCountNum;
    };

    auto drawSorting = [&]
    (HightlightType hightlighttype, int swapele1, int swapele2)
    {
        if(window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            sound.setPitch(0.01 * pillars_value[swapele2]);
            sound.play();
    
            window.clear();
            
            for(unsigned int i = 0; i < pillars.size(); i++)
            {
                pillars[i].setSize(sf::Vector2f(PILLAR_WIDTH, - PILLAR_HEIGHT * (*(pillars_value + i))));
                pillars[i].setPosition(30 + (PILLAR_WIDTH + 2) * i , 800.f); //plus 2 pixel for the outline of the rectangle
                if(i == (unsigned int)swapele1 || i == (unsigned int)swapele2)
                {
                    if(hightlighttype == HightlightType::Compare)
                        pillars[i].setFillColor(sf::Color::Yellow);
                    else if(hightlighttype == HightlightType::Write)
                        pillars[i].setFillColor(sf::Color::Blue);
                }
                else
                    pillars[i].setFillColor(sf::Color::White);

                window.draw(pillars[i]);
            }
            window.draw(sortNameText);

            if(hightlighttype == HightlightType::Compare)
                compareCount++;
            if(hightlighttype == HightlightType::Write)
                writeArrayCount++;
             
            window.draw(writeTextVisual());
            window.draw(compareTextVisual());
            window.display();
        }
    };
    switch(type)
    {
        case SortType::Insertion:
        {
            Insertion(pillars_value, pillars_value + PILLAR_SIZE, drawSorting);
            break;
        }
        
        case SortType::Selection:
        {
            Selection(pillars_value, pillars_value + PILLAR_SIZE, drawSorting);
            break;
        }
        
        case SortType::Bubble:
        {
            Bubble(pillars_value, pillars_value + PILLAR_SIZE, drawSorting);
            break;
        }

        case SortType::Shell:
        {
            break;
        }
        
        case SortType::Merge:
        {
            MergeRec(pillars_value, pillars_value + PILLAR_SIZE, 0, drawSorting);
            break;
        }
        
        case SortType::Quick:
        {
            QuickRec(pillars_value, pillars_value + PILLAR_SIZE, 0, drawSorting);
            break;
        }

        case SortType::Heap:
        {
            Heap(pillars_value, pillars_value + PILLAR_SIZE, drawSorting);
            break;
        }
    }
}

static inline sf::Font ConfigFont()
{
    sf::Font sortfont;
    if(!sortfont.loadFromFile("res/sugar snow.ttf"))
    {
        std::cout<<"load font fail!!"<<std::endl;
    }

    return sortfont;
}

static inline void SetSortNameText(sf::Text& sorttype, SortType type)
{
    sorttype.setStyle(sf::Text::Regular);
    sorttype.setPosition(100, 20);

    switch(type) 
    {
        case SortType::Insertion:
        {
            sorttype.setString("insertion sort");
            break;
        }

        case SortType::Selection:
        {
            sorttype.setString("selection sort");
            break;
        }

        case SortType::Bubble:
        {
            sorttype.setString("bubble sort");
            break;
        }

        case SortType::Shell:
        {
            break;
        }

        case SortType::Merge:
        {
            sorttype.setString("merge sort");
            break;
        }

        case SortType::Quick:
        {
            sorttype.setString("quick sort");
            break;
        }
        
        case SortType::Heap:
        {
            sorttype.setString("heap sort");
            break;
        }
    }
}

static inline void RandomizePillarVal(int* pillars_value)
{

    std::array<int, PILLAR_SIZE> arr;
    for(int i = 0; i < PILLAR_SIZE; i++)
    {
        arr[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 prng(rd());
    std::shuffle(arr.begin(), arr.end(), prng);

    for(int i = 0; i < PILLAR_SIZE; i++)
    {
        pillars_value[i] = arr[i];
        std::cout << pillars_value[i] << " ";
    }
}
