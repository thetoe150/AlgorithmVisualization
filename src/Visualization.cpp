#include "Visualization.hpp"

const float pillar_width = 10.f; 
const float pillar_height = 6.f;
const int pillar_size = 100;  


void visualizeSorting(SortType type)
{

    long int compareCount = 0;
    long int writeArrayCount = 0;
    sf::RenderWindow window(sf::VideoMode(1250, 850), "algorithm visualization");
    window.setFramerateLimit(20);

    //setup font and sort info
    sf::Font sortfont;
    if(!sortfont.loadFromFile("res/sugar snow.ttf"))
    {
        std::cout<<"load font fail!!"<<std::endl;
    }

    sf::Text sorttype("default", sortfont, 15);
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

    sf::Text staticText("comparation count: \n \n data write count:", sortfont, 15);
    staticText.setStyle(sf::Text::Regular);
    staticText.setPosition(100, 50);
    //setup the sorted array
    std::array<int, pillar_size> arr; 
    for(int i = 0; i < pillar_size; i++)
    {
        arr[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 prng(rd());
    std::shuffle(arr.begin(), arr.end(), prng);

    int pillars_value[pillar_size] = {0};

    for(int i = 0; i < pillar_size; i++)
    {
        pillars_value[i] = arr[i];
        std::cout << pillars_value[i] << " ";
    }
    //sort<int>::mergerec(pillars_value, pillars_value + pillar_size);
    //sort<int>::print(pillars_value, pillars_value + pillar_size);
    
    //setup the pillars
    std::array<sf::RectangleShape, pillar_size> pillars;
    for(unsigned int i = 0; i < pillars.size(); i++)
    {
        pillars[i].setFillColor(sf::Color::White);
        pillars[i].setOutlineColor(sf::Color::Black);
        pillars[i].setOutlineThickness(2.f);
    }

    auto compareTextVisual = [&compareCount, &sortfont]() -> sf::Text
    { 
        compareCount++;
        sf::Text compareCountNum(std::to_string(compareCount), sortfont, 15);
        compareCountNum.setPosition(265, 49); 
        return compareCountNum;
    };
    
    auto writeTextVisual = [&writeArrayCount, &sortfont]() -> sf::Text
    { 
        writeArrayCount++;
        sf::Text writeCountNum(std::to_string(writeArrayCount), sortfont, 15);
        writeCountNum.setPosition(265, 78); 
        return writeCountNum;
    };

    auto drawSorting = [&window, &pillars_value, &pillars, staticText, sorttype, compareTextVisual, writeTextVisual]
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

            window.clear();
            
            for(unsigned int i = 0; i < pillars.size(); i++)
            {
                pillars[i].setSize(sf::Vector2f(pillar_width, - pillar_height * (*(pillars_value + i))));
                pillars[i].setPosition(30 + (pillar_width + 2) * i , 800.f); //plus 2 pixel for the outline of the rectangle
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
            window.draw(staticText);
            window.draw(sorttype);
            window.draw(compareTextVisual());
            window.draw(writeTextVisual());
             
            window.display();
        }
    };
    switch(type)
    {
        case SortType::Insertion:
        {
            Insertion(pillars_value, pillars_value + pillar_size, drawSorting);
            break;
        }
        
        case SortType::Selection:
        {
            Selection(pillars_value, pillars_value + pillar_size, drawSorting);
            break;
        }
        
        case SortType::Bubble:
        {
            Bubble(pillars_value, pillars_value + pillar_size, drawSorting);
            break;
        }
        
        case SortType::Merge:
        {
            MergeRec(pillars_value, pillars_value + pillar_size, 0, drawSorting);
            break;
        }
        
        case SortType::Quick:
        {
            QuickRec(pillars_value, pillars_value + pillar_size, 0, drawSorting);
            break;
        }

        case SortType::Heap:
        {
            Heap(pillars_value, pillars_value + pillar_size, drawSorting);
            break;
        }
    }
}

void printresult(int* start, int* end)
{
    while(start != end)
    {
        std::cout<<*start<<" ";
        start++;
    }
}

void Insertion(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
{
    int size = end - start;
    for(int i = 1; i < size; i++)
    {
        int temp = *(start + i);
        int j = i - 1;
        int max_temp = *(start + j);
        while(temp < *(start + j - 1) && j - 1 >= 0)
        {
            drawSorting(HightlightType::Compare, i, j - 1);
            drawSorting(HightlightType::Write, j, j);
            *(start + j) = *(start + j - 1);
            j--;
        }
        *(start + j) = temp;
        *(start + i) = max_temp;
    }
}

void Selection(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
    {
    int size = end - start;
    for(int i = 0; i < size - 1; i++)
        {
            int min = *(start + i);
            int min_idx = i;
            for(int j = i + 1; j < size; j++)
            {
                drawSorting(HightlightType::Compare, min_idx, j);
                if(*(start + j) < min)
                {
                    min = *(start + j);
                    min_idx = j;
                }
            }
            int temp = *(start + i);
            *(start + i) = *(start + min_idx);
            *(start + min_idx) = temp;
            drawSorting(HightlightType::Write, min_idx, i);
        }
    }

void Bubble(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
{
   bool sorted = true;
   int size = end - start;
    for(int i = 0; i < size - 1; i++)
    {
        sorted = true;
        for(int j = size - 1; j > i; j--)
        {
            drawSorting(HightlightType::Compare, j - 1, j);
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

void Merge(int* start, int* mid, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
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
        drawSorting(HightlightType::Compare, abs_pos + FHwalker, abs_pos + FHsize + SHwalker);
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
        drawSorting(HightlightType::Write, abs_pos + FHwalker, abs_pos + FHsize);
        mergeWalker++;
    }
    while(SHwalker < SHsize)
    {
        *mergeWalker = SHarray[SHwalker++];
        drawSorting(HightlightType::Write, abs_pos + FHwalker + SHwalker, abs_pos + FHsize + SHwalker);
        mergeWalker++;
    }

   delete[] FHarray;
   delete[] SHarray;
}

void MergeRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   if(size == 1)
      return;
   
   int* mid = start + (size / 2);
   MergeRec(start, mid, abs_pos, drawSorting);
   MergeRec(mid, end, abs_pos + (size/2), drawSorting);
   Merge(start, mid, end, abs_pos, drawSorting);
}

int* Quick(int* start, int* pivot, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   int Lwalker = 0;
   int Rwalker = size - 1;

   while(Rwalker >= Lwalker && Rwalker > 0)
   {
        drawSorting(HightlightType::Compare, abs_pos + Lwalker, abs_pos + pivot - start);
        drawSorting(HightlightType::Compare, abs_pos + Rwalker, abs_pos + pivot - start);

        if(*(start + Lwalker) > *pivot && *(start + Rwalker) < *pivot)
        {
            int temp = *(start + Lwalker);
            *(start + Lwalker) = *(start + Rwalker);
            *(start + Rwalker) = temp;
            drawSorting(HightlightType::Write, abs_pos + Lwalker, abs_pos + Rwalker);
            Lwalker++;
            Rwalker--;
        }
        else if(*(start + Lwalker) > *pivot && *(start + Rwalker) >= *pivot)
        {
            Rwalker--;
        }
        else if(*(start + Lwalker) <= *pivot && *(start + Rwalker) < *pivot)
        {
            Lwalker++;
        }
        else 
        {
            Rwalker--;
            Lwalker++;
        }
   }

   if(Lwalker - (pivot - start) == 1 
      && (pivot - start) - Rwalker == 1)
      return pivot;
   
   if(Lwalker > pivot - start)
   {
        int temp = *(start + Rwalker);   
        *(start + Rwalker) = *pivot;
        *pivot = temp;
        drawSorting(HightlightType::Write, abs_pos + Rwalker, abs_pos + pivot - start);
        return start + Rwalker;
   }
   else
   {
        int temp = *(start + Lwalker);   
        *(start + Lwalker) = *pivot;
        *pivot = temp;
        drawSorting(HightlightType::Write, abs_pos + Lwalker, abs_pos + pivot - start);
        return start + Lwalker;
   }
}

void QuickRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   if(size <= 1)
      return;
   
   int* mid = start + (size / 2); 
   int* pivot = Quick(start, mid, end, abs_pos, drawSorting);
   QuickRec(start, pivot, abs_pos, drawSorting);
   QuickRec(pivot + 1, end, abs_pos + (pivot - start) + 1, drawSorting);
}

void reheapUp(int* start, int* end, int reheapIdx, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int lastIdx = end - start - 1;
    int reheapToLast = lastIdx - reheapIdx;
    int* lastEle = end - 1;
    int* reheapEle = lastEle - reheapToLast;

    while(reheapToLast > 0)
    {
        int* parentEle = lastEle - (reheapToLast - 1)/2; //std::cout<<"parent: "<<*parentEle<<"  reheap: "<<*reheapEle<<std::endl;
        compareVisualize(HightlightType::Compare, lastIdx - reheapToLast, lastIdx - (reheapToLast - 1)/2);
        if(*reheapEle < *parentEle)
        {
            int temp = *reheapEle;
            *reheapEle = *parentEle;
            *parentEle = temp;
            compareVisualize(HightlightType::Write, lastIdx - reheapToLast, lastIdx - (reheapToLast - 1)/2);
            reheapEle = parentEle;
            reheapToLast = (reheapToLast - 1)/2;
        }
        else break;
    } 
}

void reheapDown(int* start, int* end, int ignoreEle, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int lastIdx = end - start - 1;  //consider last Idx of the array as root and as index 0
    int finalHeapEleToLast = lastIdx - ignoreEle - 1;

    int parentIdxToLast = 0;
    int leftIdxToLast = parentIdxToLast * 2 + 1;
    int rightIdxToLast = parentIdxToLast * 2 + 2;
    int* lastEle = end - 1;

    while(leftIdxToLast <= finalHeapEleToLast)
    {
        int largest = parentIdxToLast;

        compareVisualize(HightlightType::Compare, lastIdx - largest, lastIdx - leftIdxToLast);
        if(*(lastEle - leftIdxToLast) < *(lastEle - largest)) 
        {
            largest = leftIdxToLast;
        }

        compareVisualize(HightlightType::Compare, lastIdx - largest, lastIdx - rightIdxToLast);
        if(rightIdxToLast < finalHeapEleToLast
        && *(lastEle - rightIdxToLast) < *(lastEle - largest)) 
        {
            largest = rightIdxToLast;
        }

        if(largest != parentIdxToLast)
        {
            int temp = *(lastEle - largest);
            *(lastEle - largest) = *(lastEle - parentIdxToLast);
            *(lastEle - parentIdxToLast) = temp;
            compareVisualize(HightlightType::Write, lastIdx - largest, lastIdx - parentIdxToLast);

            parentIdxToLast = largest;
            leftIdxToLast = parentIdxToLast * 2 + 1;
            rightIdxToLast = parentIdxToLast * 2 + 2;

        }
        else break;

    }

}
void Heap(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int size = end - start;
    for(int i = size - 2; i >= 0; i--)
    {
        reheapUp(start, end, i, compareVisualize); //print(start, end);
    }

    for(int i = 0; i < size - 1; i++)
    {
        int temp = *(end - 1);
        *(end - 1) = *(start + i);
        *(start + i) = temp;
        compareVisualize(HightlightType::Write, i, end - start - 1);
        reheapDown(start, end, i, compareVisualize);
    }

}