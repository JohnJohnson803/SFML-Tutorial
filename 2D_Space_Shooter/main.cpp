#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <cstdlib>

class Player
{
public:
    sf::Sprite shape;
    sf::Texture* texture;
    int HP;
    int HPMax;

    Player(sf::Texture *texture)
    {   
        this->HPMax = 10;
        this->HP = this->HPMax;

        this->texture = texture;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.1f, 0.1f);
    }

    ~Player(){};

};

class Enemy
{
    public:

};

class Bullet
{
    public:

};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "2D Space Game");
    window.setFramerateLimit(60);

    //Init Textures
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("textures/ship.png"))
    {
        throw("Could not load Player Texture!");
    }

    Player player(&playerTexture);

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
        window.draw(player.shape);
    }
}