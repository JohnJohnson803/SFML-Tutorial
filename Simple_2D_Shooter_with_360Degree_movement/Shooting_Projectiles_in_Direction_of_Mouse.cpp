#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Works");
    window.setFramerateLimit(60);

    sf::CircleShape shape;
    shape.setRadius(30.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(30,30);

    sf::CircleShape bullet;
    std::vector<sf::CircleShape> bullets;
    std::vector<float> angles;
    

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            shape.move(-5,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            shape.move(5,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            shape.move(0,-5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            shape.move(0,5);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bullets.push_back(sf::CircleShape());
            bullets.back().setRadius(5);
            bullets.back().setOrigin(5,5);
            bullets.back().setPosition(shape.getPosition());
            angles.push_back(atan2(sf::Mouse::getPosition(window).y - shape.getPosition().y, sf::Mouse::getPosition(window).x - shape.getPosition().x));
        }

        window.clear();
        window.draw(shape);

    for(int i=0; i<bullets.size(); i++)
        {
            bullets[i].move(5*cos(angles[i]), 5*sin(angles[i]));
            window.draw(bullets[i]);
        }

        window.display();
    }


    return 0;
}

