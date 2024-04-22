#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>

class Bullet
{
    public:
    sf::CircleShape shape;
    sf::Vector2f currVelocity;
    float maxSpeed;


    Bullet(float radius = 5.f): currVelocity(0.f, 0.f), maxSpeed(15.f)
    {
        this->shape.setRadius(radius);
        this->shape.setFillColor(sf::Color::Red);
    };

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "2D Shooter with 360 degree movement");
    window.setFramerateLimit(60);
    sf::Event event;

    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::White);

    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;


    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            window.close();
        }

        //UPDATE
        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
        mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

        //Player
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0.f, -10.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-10.f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0.f, 10.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(10, 0.f);


        //DRAW
        window.clear();

        window.draw(player);


        window.display();

    }
        return 0;
}