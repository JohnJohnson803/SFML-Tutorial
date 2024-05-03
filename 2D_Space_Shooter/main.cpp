#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <cstdlib>


int main()
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "2D Space Game");
    sf::Event event;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        //Update 

        //Draw
    }
}