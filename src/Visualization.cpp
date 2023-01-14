#include "Visualization.hpp"

const float PILLAR_WIDTH = 10.f; 
const float PILLAR_HEIGHT = 6.f;
const int PILLAR_SIZE = 100;  


void visualizeSorting(SortType type)
{

    long int compareCount = 0;
    long int writeArrayCount = 0;
    sf::RenderWindow window(sf::VideoMode(1250, 850), "Algorithm Visualization");
    window.setFramerateLimit(60);

    //setup Font and sort info
    sf::Font SortFont;
    if(!SortFont.loadFromFile("res/Sugar Snow.ttf"))
    {
        std::cout<<"Load Font Fail!!"<<std::endl;
    }

    sf::Text sortType("Default", SortFont, 15);
    sortType.setStyle(sf::Text::Regular);
    sortType.setPosition(100, 20);

    switch(type) 
    {
        case SortType::Insertion:
        {
            sortType.setString("Insertion Sort");
            break;
        }

        case SortType::Selection:
        {
            sortType.setString("Selection Sort");
            break;
        }

        case SortType::Bubble:
        {
            sortType.setString("Bubble Sort");
            break;
        }

        case SortType::Merge:
        {
            sortType.setString("Merge Sort");
            break;
        }
    }

    sf::Text StaticText("Comparation Count: \n \n Data write Count:", SortFont, 15);
    StaticText.setStyle(sf::Text::Regular);
    StaticText.setPosition(100, 50);
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
    //Sort<int>::MergeRec(pillars_value, pillars_value + PILLAR_SIZE);
    //Sort<int>::print(pillars_value, pillars_value + PILLAR_SIZE);
    
    //setup the pillars
    std::array<sf::RectangleShape, PILLAR_SIZE> pillars;
    for(unsigned int i = 0; i < pillars.size(); i++)
    {
        pillars[i].setFillColor(sf::Color::White);
        pillars[i].setOutlineColor(sf::Color::Black);
        pillars[i].setOutlineThickness(2.f);
    }

    auto compareTextVisual = [&compareCount, &SortFont]() -> sf::Text
    { 
        compareCount++;
        sf::Text compareCountNum(std::to_string(compareCount), SortFont, 15);
        compareCountNum.setPosition(265, 49); 
        return compareCountNum;
    };
    
    auto writeTextVisual = [&writeArrayCount, &SortFont]() -> sf::Text
    { 
        writeArrayCount++;
        sf::Text WriteCountNum(std::to_string(writeArrayCount), SortFont, 15);
        WriteCountNum.setPosition(265, 78); 
        return WriteCountNum;
    };

    auto sortingVisualize = [&window, &pillars_value, &pillars, StaticText, sortType, compareTextVisual, writeTextVisual]
    (HightlightType hightlighttype, int swapEle1, int swapEle2)
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
                pillars[i].setSize(sf::Vector2f(PILLAR_WIDTH, - PILLAR_HEIGHT * (*(pillars_value + i))));
                pillars[i].setPosition(30 + (PILLAR_WIDTH + 2) * i , 800.f); //plus 2 pixel for the outline of the rectangle
                if(i == (unsigned int)swapEle1 || i == (unsigned int)swapEle2)
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
            window.draw(StaticText);
            window.draw(sortType);
            window.draw(compareTextVisual());
            window.draw(writeTextVisual());
             
            window.display();
        }
    };
    switch(type)
    {
        case SortType::Insertion:
        {
            Insertion(pillars_value, pillars_value + PILLAR_SIZE, sortingVisualize);
            break;
        }
        
        case SortType::Selection:
        {
            Selection(pillars_value, pillars_value + PILLAR_SIZE, sortingVisualize);
            break;
        }
        
        case SortType::Bubble:
        {
            Bubble(pillars_value, pillars_value + PILLAR_SIZE, sortingVisualize);
            break;
        }
        
        case SortType::Merge:
        {
            MergeRec(pillars_value, pillars_value + PILLAR_SIZE, 0, sortingVisualize);
            break;
        }
    }
}

void printResult(int* start, int* end)
{
    while(start != end)
    {
        std::cout<<*start<<" ";
        start++;
    }
}

void Insertion(int* start, int* end, std::function<void (HightlightType, int, int)> sortingVisualize)
{
    int size = end - start;
    for(int i = 1; i < size; i++)
    {
        int temp = *(start + i);
        int j = i - 1;
        int max_temp = *(start + j);
        while(temp < *(start + j - 1) && j - 1 >= 0)
        {
            sortingVisualize(HightlightType::Compare, i, j - 1);
            sortingVisualize(HightlightType::Write, j, j);
            *(start + j) = *(start + j - 1);
            j--;
        }
        *(start + j) = temp;
        *(start + i) = max_temp;
    }
}

void Selection(int* start, int* end, std::function<void (HightlightType, int, int)> sortingVisualize)
    {
    int size = end - start;
    for(int i = 0; i < size - 1; i++)
        {
            int min = *(start + i);
            int min_idx = i;
            for(int j = i + 1; j < size; j++)
            {
                sortingVisualize(HightlightType::Compare, min_idx, j);
                if(*(start + j) < min)
                {
                    min = *(start + j);
                    min_idx = j;
                }
            }
            int temp = *(start + i);
            *(start + i) = *(start + min_idx);
            *(start + min_idx) = temp;
            sortingVisualize(HightlightType::Write, min_idx, i);
        }
    }

void Bubble(int* start, int* end, std::function<void (HightlightType, int, int)> sortingVisualize)
{
   bool sorted = true;
   int size = end - start;
    for(int i = 0; i < size - 1; i++)
    {
        sorted = true;
        for(int j = size - 1; j > i; j--)
        {
            sortingVisualize(HightlightType::Compare, j - 1, j);
            if(*(start + j) < *(start + j - 1))
            {
                sorted = false;
                int temp = *(start + j);
                *(start + j) = *(start + j - 1);
                *(start + j - 1) = temp;
            }
        }
        if(sorted) break;
    }
}

void Merge(int* start, int* mid, int* end, int abs_pos, std::function<void (HightlightType, int, int)> sortingVisualize)
{
   int FHsize = mid - start; 
   int SHsize = end - mid; 

   int *FHarray = new int[FHsize];
   int *SHarray = new int[SHsize];

   for(int i = 0; i < FHsize; i++)
   {
      FHarray[i] = *(start + i);
   }

   for(int i = 0; i < SHsize; i++)
   {
      SHarray[i] = *(mid + i);
   }
   int* mergeWalker = start;
   int FHwalker = 0;
   int SHwalker = 0;
   while(FHwalker < FHsize && SHwalker < SHsize)
   {
        sortingVisualize(HightlightType::Compare, abs_pos + FHwalker, abs_pos + FHsize + SHwalker);
        if(FHarray[FHwalker] <= SHarray[SHwalker])
        {
            *mergeWalker = FHarray[FHwalker++];
        }
        else
        {
            *mergeWalker = SHarray[SHwalker++];
        }
        mergeWalker++;
    }

    while(FHwalker < FHsize) 
    {
        *mergeWalker = FHarray[FHwalker++];
        mergeWalker++;
    }
    while(SHwalker < SHsize)
    {
        *mergeWalker = SHarray[SHwalker++];
        mergeWalker++;
    }

   delete[] FHarray;
   delete[] SHarray;
}

void MergeRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> sortingVisualize)
{
   int size = end - start;
   if(size == 1)
      return;
   
   int* mid = start + (size / 2);
   MergeRec(start, mid, abs_pos, sortingVisualize);
   MergeRec(mid, end, abs_pos + (size/2), sortingVisualize);
   Merge(start, mid, end, abs_pos, sortingVisualize);
}
