#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Texts and Fonts");
    sf::Event event;

    sf::Font font;
    
    if(!font.loadFromFile("Fonts/Jacquard12Charted-Regular.ttf"))
    {
        throw("COULD NOT LOAD FONT!");
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(64);
    //text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Magenta);
    text.setString("HEY I AM A STRING OF TEXT IN SFML");
    text.setPosition(10.f, window.getSize().y / 2);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}