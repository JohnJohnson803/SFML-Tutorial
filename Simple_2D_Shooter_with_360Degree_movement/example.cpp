#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>

class Bullets
{
    public:
    sf::CircleShape bullet;
    float angle;

    Bullets()
    {
        this->bullet.setRadius(5.f);
        this->bullet.setFillColor(sf::Color::Magenta);
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Example");
    sf::Event event;

    sf::CircleShape player;
    sf::Vector2f playerCenter;
    player.setRadius(30.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(window.getSize().x / 2, window.getSize().y - player.getRadius()*2.5);

    //Projectiles
    Bullets b1;
    std::vector<Bullets> projectiles;

    //Enemies 
    sf::RectangleShape enemy;
    enemy.setSize(sf::Vector2f(30.f, 30.f));
    enemy.setFillColor(sf::Color::White);
    std::vector<sf::RectangleShape> enemies;


    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();

        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

        //Player Movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0, -5.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0, 5.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-5.f, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(5.f, 0);

        //Firing Projectiles
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            b1.bullet.setPosition(playerCenter);
            b1.angle = atan2(sf::Mouse::getPosition(window).y - playerCenter.y, sf::Mouse::getPosition(window).x - playerCenter.x);
            projectiles.push_back(Bullets(b1));

        }

        for(size_t i=0; i<projectiles.size(); i++)
        {
            projectiles[i].bullet.move(5*cos(projectiles[i].angle), 5*sin(projectiles[i].angle));
            window.draw(projectiles[i].bullet);
        }

        

        window.draw(player);
        window.display();
    }

    return 0;
}


