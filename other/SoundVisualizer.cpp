#include "main.hpp"

const float SAMPLE_SHAPE_WIDTH = 0.1;
const float SAMPLE_SHAPE_HEIGHT = 300.f;
const int FRAME_RATE = 60;

int main(int argc, char* argv[])
{
    if(argc < 2)
        return 1;
    
    const std::string soundSrc(argv[1]);
    sf::SoundBuffer soundBuffer;

    if(!soundBuffer.loadFromFile(soundSrc))
        std::cout<<"Fail to load sound file"<<std::endl;

    sf::Sound sound(soundBuffer);

    sf::OutputSoundFile output_sound;

    try
    {
        if(!output_sound.openFromFile("res/goofy-ahh-full.wav", 441, 1))
        {
            std::cout<<"Fail to load output sound file"<<std::endl;
        }

    }
    catch(const std::exception& e)
    {

        std::cerr << "Errrrrrrrrrrrrrrrrrrrrrrrror: "<< e.what() << '\n';
    }

    //output_sound.write(soundBuffer.getSamples(), soundBuffer.getSampleCount());

    const int16_t* sampleArr = soundBuffer.getSamples();
    uint16_t sampleCount = soundBuffer.getSampleCount();

    for(int i = 0; i < sampleCount; i++)
    {
       std::cout<<sampleArr[i]<<" ";
    }


    sf::RenderWindow window(sf::VideoMode(1250, 850), "Visualize Sound");
    window.setFramerateLimit(FRAME_RATE);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        try
        {
            for(int i = 0; i < sampleCount; ++i)
            {
                sf::RectangleShape sampleShape;
                sampleShape.setFillColor(sf::Color::White);
                sampleShape.setOutlineColor(sf::Color::Black);
                sampleShape.setSize(sf::Vector2f(SAMPLE_SHAPE_WIDTH, SAMPLE_SHAPE_HEIGHT * sampleArr[i] / 32000.f));
                sampleShape.setPosition(30 + SAMPLE_SHAPE_WIDTH * i, 400.f);

                //sampleShapeArr.push_back(sampleShape);
                window.draw(sampleShape); 
            }

        }
        catch(const std::exception& e)
        {
            std::cout << "Errrrrrrrrrrrrrrrrrrrrrrrror: "<< e.what() << '\n';
        }
        

        window.display();

    }

    return 0;
}