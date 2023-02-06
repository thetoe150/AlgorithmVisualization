#include "main.hpp"
#include "Visualization.hpp"

const int PILLAR_SIZE = 100;

int main(int argc, char *argv[]){
    //int array[10] = {6,4,2,18,1,8,33,12,7,0};
    //Sort<int>::print(array, array + 10);
    //Sort<int>::Insertion(array, array + 10);
    //Sort<int>::Selection(array, array + 10);
    //Sort<int>::Bubble(array, array + 10);
    //Sort<int>::MergeRec(array, array + 10);
    //Sort<int>::print(array, array + 10);
    //Sort<int>::QuickRec(array, array + 10);
    //Sort<int>::Heap(array, array + 10);
    //Sort<int>::print(array, array + 10);

    std::unordered_map<std::string, SortType> sortMap;
    sortMap["Insertion"] = SortType::Insertion;
    sortMap["Selection"] = SortType::Selection;
    sortMap["Bubble"] = SortType::Bubble;
    sortMap["Shell"] = SortType::Shell;
    sortMap["Merge"] = SortType::Merge;
    sortMap["Quick"] = SortType::Quick;
    sortMap["Heap"] = SortType::Heap;

    if(argc < 2) return 1;
    std::string sortTypeStr(argv[1]);
    switch(sortMap[sortTypeStr])
    {
        case SortType::Selection:{
            VisualizeSorting(SortType::Selection);
            break;
        }
        case SortType::Insertion:{
            VisualizeSorting(SortType::Insertion);
            break;
        }
        case SortType::Bubble:{
            VisualizeSorting(SortType::Bubble);
            break;
        }
        case SortType::Shell:{
            VisualizeSorting(SortType::Shell);
            break;
        }
        case SortType::Merge:{
            VisualizeSorting(SortType::Merge);
            break;
        }
        case SortType::Quick:{
            VisualizeSorting(SortType::Quick);
            break;
        }
        case SortType::Heap:{
            VisualizeSorting(SortType::Heap);
            break;
        }
    }
    
    return 0;
}

//int main()
//{
    //// create the window
    //sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    //window.setVerticalSyncEnabled(true);

    //// activate the window
    //window.setActive(true);

    //// load resources, initialize the OpenGL states, ...

    //// run the main loop
    //bool running = true;
    //while (running)
    //{
        //// handle events
        //sf::Event event;
        //while (window.pollEvent(event))
        //{
            //if (event.type == sf::Event::Closed)
            //{
                //// end the program
                //running = false;
            //}
            //else if (event.type == sf::Event::Resized)
            //{
                //// adjust the viewport when the window is resized
                //glViewport(0, 0, event.size.width, event.size.height);
            //}
            //display();
        //}

        //// clear the buffers
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// draw...

        //// end the current frame (internally swaps the front and back buffers)
        //window.display();
    //}

    //// release resources...

    //return 0;
//}