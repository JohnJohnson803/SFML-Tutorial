#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Cat do(d)ge");
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



    //Doge

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                    window.close();
                }
        }

        window.clear();
        
        for(size_t i =0; cats.size(); i++)
        {
            window.draw(cats[i]);
        }

    
        window.display();
    }

    return 0;
}