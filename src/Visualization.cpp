#include "Visualization.hpp"

static inline void ConfigSound(sf::Sound soundPool[], sf::SoundBuffer& buffer, const std::string& src)
{
    if(!buffer.loadFromFile(src))
        std::cout<<"fail to load sound source"<<std::endl;
        
    //int sampleCount = buffer.getSampleCount();
    //const int16_t *sampleArr = new int16_t[sampleCount];
    //sampleArr = buffer.getSamples();

    //for(int i = 0; i < sampleCount; i++)
    //{
        //std::cout<<sampleArr[i]<<" ";
    //}

    //std::cout <<"sound.getLoop(): "<<sound.getLoop() << std::endl;
    std::cout <<"buffer.getDuration(): " <<buffer.getDuration().asMicroseconds() << std::endl;
    //sound.setPitch(0.01);
    for(int i = 0; i < SOUND_POOL_SIZE; i++)
    {
        soundPool[i].setBuffer(buffer);
        soundPool[i].setVolume(50);
    }

    std::cout<<"Sample rate: "<< buffer.getSampleRate()<<std::endl;
}

static inline void PlaySoundFromPool(sf::Sound soundPool[], float pitch)
{
    int idle = 0;
    for(int i = 0; i < SOUND_POOL_SIZE; i++)
    {
        //only play sound that not has been playing
        if(soundPool[i].getStatus() == sf::SoundSource::Status::Playing)
        {
            if(soundPool[i].getPitch() == pitch)
                return;
        }
        if(soundPool[i].getStatus() == sf::SoundSource::Status::Stopped)
        {
            idle = i;
        }
    }

    soundPool[idle].setPitch(pitch);
    soundPool[idle].play();
    //std::cout  <<pitch<<" ";
}

void VisualizeSorting(SortType type, int n)
{
    sf::Sound sounds[SOUND_POOL_SIZE];
    sf::SoundBuffer buffer;
    std::string src = "res/goofy-ahh.wav";
    ConfigSound(sounds, buffer, src);

    long int compareCount = 0;
    long int writeArrayCount = 0;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "algorithm visualization");
    window.setFramerateLimit(FRAME_RATE);

    //setup font and sort info
    sf::Font sortFont = ConfigFont();
    
    sf::Text sortNameText("default", sortFont, 25);
    SetSortNameText(sortNameText, type);

    //random array values
	int* pillars_value = new int[n];
    RandomizePillarVal(pillars_value, n);

    //sort<int>::mergerec(pillars_value, pillars_value + pillar_size);
    //sort<int>::print(pillars_value, pillars_value + pillar_size);
    
    //setup the pillars
    std::vector<sf::RectangleShape> pillars;
    for(unsigned int i = 0; i < n; i++)
    {
		sf::RectangleShape pillar;
        pillar.setFillColor(sf::Color::White);
        pillar.setOutlineColor(sf::Color::Black);
        pillar.setOutlineThickness(OUTLINE_WIDTH);
		pillars.push_back(pillar);
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
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
            }

			float pitch_step = (HIGHTEST_PITCH - LOWEST_PITCH) / n;
            if(hightlighttype == HightlightType::Compare)
            {
                PlaySoundFromPool(sounds, LOWEST_PITCH + pitch_step * pillars_value[swapele1]);
                PlaySoundFromPool(sounds, LOWEST_PITCH + pitch_step * pillars_value[swapele2]);
            }
            //else 
                //PlaySoundFromPool(sounds, 0.01 * pillars_value[swapele2]);
    
            window.clear();
            
			// @speed: redraw every pillar even if unchange
            for(unsigned int i = 0; i < pillars.size(); i++)
            {
				float pillar_width_unit = (WINDOW_WIDTH - OFFSET_SIDE * 2) / n - OUTLINE_WIDTH * 2;
				float pillar_height_unit = (WINDOW_HEIGHT - OFFSET_TOP + OFFSET_BOT) / n;
                pillars[i].setSize(sf::Vector2f(pillar_width_unit,
								- pillar_height_unit * (*(pillars_value + i))));
                pillars[i].setPosition((pillar_width_unit + OUTLINE_WIDTH * 2) * i + OFFSET_SIDE,
									   WINDOW_HEIGHT - OFFSET_BOT); //plus 2 pixel for the outline of the rectangle
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
	 
	Timer a("Sort and Visualize time");
    switch(type)
    {
        case SortType::Insertion:
        {
            Insertion(pillars_value, pillars_value + n, drawSorting);
            break;
        }
        
        case SortType::Selection:
        {
            Selection(pillars_value, pillars_value + n, drawSorting);
            break;
        }
        
        case SortType::Bubble:
        {
            Bubble(pillars_value, pillars_value + n, drawSorting);
            break;
        }

        case SortType::Shell:
        {
            Shell(pillars_value, pillars_value + n, SHELL_STEP_ARRAY, sizeof(SHELL_STEP_ARRAY) / sizeof(int), drawSorting);
            break;
        }
        
        case SortType::Merge:
        {
            MergeRec(pillars_value, pillars_value + n, 0, drawSorting);
            break;
        }
        
        case SortType::Quick:
        {
            QuickRec(pillars_value, pillars_value + n, 0, drawSorting);
            break;
        }

        case SortType::Heap:
        {
            Heap(pillars_value, pillars_value + n, drawSorting);
            break;
        }
        
        case SortType::LSD_Radix:
        {
            LSD_Radix(pillars_value, pillars_value + n, drawSorting);
            break;
        }
        
        case SortType::MSD_Radix:
        {
            MSD_Radix(pillars_value, pillars_value + n, drawSorting);
            break;
        }
        
       case SortType::Bogo:
        {
            Bogo(pillars_value, pillars_value + n, drawSorting);
            break;
        }
    }

    std::cout<<"Sorted array: "<<std::endl;
    for(int i = 0; i < n; i++)
    {
        std::cout << pillars_value[i] << " ";
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
            sorttype.setString("shell sort");
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

        case SortType::LSD_Radix:
        {
            sorttype.setString("lsd radix sort");
            break;
        }
        
        case SortType::MSD_Radix:
        {
            sorttype.setString("msd radix sort");
            break;
        }

        case SortType::Bogo:
        {
            sorttype.setString("bogo sort");
            break;
        }
    }
}

static inline void RandomizePillarVal(int* pillars_value, int n)
{
	Timer a("Random time");
    std::vector<int> arr;
    for(int i = 1; i <= n; i++)
    {
		arr.push_back(i);
    }

    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout <<"current time: "<< tt <<std::endl;

    std::mt19937 prng(static_cast<std::mt19937::result_type>(tt));
    std::shuffle(arr.begin(), arr.end(), prng);


    std::cout<<"Original array: "<<std::endl;
    for(int i = 0; i < n; i++)
    {
        pillars_value[i] = arr[i];
        std::cout<<pillars_value[i] << " ";
    }
    std::cout<<std::endl;
}
