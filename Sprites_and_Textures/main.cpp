#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Cat do(d)ge");
    window.setFramerateLimit(60);
    sf::Event event;

    //Cat
    sf::Texture catTex;
    sf::Sprite cat;
    
    if(!catTex.loadFromFile("textures/cat2.png"))
    {
        throw "Could not load cat2.png";
    }

    cat.setTexture(catTex);
    cat.setScale(sf::Vector2f(0.3f, 0.3f));
    std::vector<sf::Sprite> cats;
    cats.push_back(sf::Sprite(cat));
    int catSpawnTimer = 15;

    //Doge
    sf::Texture dogeTex;
    sf::Sprite doge;
    int hp = 10;
    sf::RectangleShape hpBar;
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(hp *20, 20));
    hpBar.setPosition(sf::Vector2f((window.getSize().x / 2) -20, 0));

    if(!dogeTex.loadFromFile("textures/doge2.png"))
    {
        throw "Could not load doge2.png";
    }

    doge.setTexture(dogeTex);
    doge.setScale(sf::Vector2f(0.2f, 0.2f));


    while(window.isOpen() && hp > 0)
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                    window.close();
                }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        //UPDATE
        //DOGE(PLAYER)
        doge.setPosition(doge.getPosition().x, sf::Mouse::getPosition(window).y);

        if(doge.getPosition().y > window.getSize().y - doge.getGlobalBounds().height)
        {
            doge.setPosition(doge.getPosition().x, window.getSize().y - doge.getGlobalBounds().height);
        }

        if(doge.getPosition().y < 0)
        {
            doge.setPosition(doge.getPosition().x, 0);
        }



        //CATS(ENEMIES)
        for(size_t i=0; i < cats.size(); i++)
            {
                cats[i].move(-7.f, 0);
                if(cats[i].getPosition().x < 0 - cat.getGlobalBounds().width)
                {
                    cats.erase(cats.begin() + i);
                }
            }

        if(catSpawnTimer < 15)
            catSpawnTimer++;
        
        if(catSpawnTimer >= 15)
        {
            cat.setPosition(window.getSize().x, rand()%int(window.getSize().y) - cat.getGlobalBounds().height);
            cats.push_back(sf::Sprite(cat));
            catSpawnTimer = 0;
        }

        //COLLISION
        for(size_t i=0; i<cats.size(); i++)
        {
            if(doge.getGlobalBounds().intersects(cats[i].getGlobalBounds()))
            {
                hp--;
                hpBar.setSize(sf::Vector2f(hpBar.getSize().x - 20, hpBar.getSize().y));
                cats.erase(cats.begin() + i);
            }
        }

        
        //DRAW
        window.clear();
        window.draw(hpBar);
        window.draw(doge);

        for(size_t i =0; i < cats.size(); i++)
        {
            window.draw(cats[i]);
        }

    
        window.display();
    }

    return 0;
}