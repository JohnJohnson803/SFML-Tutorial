#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Framerate Independent Gameplay");
    sf::Event event;
    window.setFramerateLimit(60);
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile("/home/johnathandjohnson803/SFML-Tutorial/2D_Space_Shooter/textures/ship.png");
    sprite.setTexture(texture);
    sprite.setScale(0.2, 0.2);

    sf::Clock clock;
    float dt; 
    float multiplier = 60.f;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        dt = clock.restart().asSeconds();

        std::cout << "dt: " << dt << "\n";

       if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
       {

       }
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
       {

       }
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
       {

       }

       if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
       {

       }
              


        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    return 0;
}