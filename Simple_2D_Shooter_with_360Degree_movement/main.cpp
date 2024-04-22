#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>

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
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1920,1080), "2D Shooter with 360 degree movement");
    window.setFramerateLimit(60);
    sf::Event event;

    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::White);

    //Vectors
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    //Bullets
    Bullet b1;
    std::vector<Bullet> bullets;
    int shootTimer = 0;

    //Enemy
    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color::Magenta);
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    std::vector<sf::RectangleShape> enemies;
    int spawnCounter = 20;


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

        if(shootTimer < 5)
        {
            shootTimer++;
        }

        //Enemies
        if(spawnCounter < 20)
        {
            spawnCounter++;
        }

        if(spawnCounter >= 20)
        {
            enemy.setPosition(sf::Vector2f(rand()%window.getSize().x, rand()%window.getSize().y));
            enemies.push_back(sf::RectangleShape(enemy));
            spawnCounter = 0;
        }
    
        //Shooting
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 5)
        {
            b1.shape.setPosition(playerCenter);
            b1.currVelocity = aimDirNorm * b1.maxSpeed;
            bullets.push_back(Bullet(b1));
            shootTimer = 0;
        }

        for(size_t i=0; i<bullets.size(); i++)
        {
            bullets[i].shape.move(bullets[i].currVelocity);
            if(bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x || bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        for(size_t i=0; i<enemies.size(); i++)
        {
            enemies[i].move(0.f, -5.f);
            if(enemies[i].getPosition().y > window.getSize().y)
            {
                enemies.erase(enemies.begin() + i);
            }
        }

        //Enemy Collision
        for(size_t i=0; i<enemies.size(); i++)
        {
            for(size_t j=0; j<bullets.size(); j++)
            {
                if(bullets[j].shape.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                {
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                }
            }
        }

        //DRAW
        window.clear();

        for(size_t i=0; i<enemies.size(); i++)
        {
            window.draw(enemies[i]);
        }

        window.draw(player);
        
        for(size_t i=0; i<bullets.size(); i++)
        {
            window.draw(bullets[i].shape);
        }


        window.display();

    }
        return 0;
}