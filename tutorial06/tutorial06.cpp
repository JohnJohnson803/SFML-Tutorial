#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void Update(sf::RenderWindow &windowOb, sf::RectangleShape &squareObj);
void Draw(sf::RectangleShape &squareObj, sf::RenderWindow &windowObj);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600),"Simple Game");
	sf::Event event;
	sf::RectangleShape square(sf::Vector2f(100.f,100.f));
	square.setFillColor(sf::Color::Red);

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.KeyPressed && event.key.code == sf::Keyboard::Escape)
					window.close();
		}
			
		//Update();
		Update(window, square);
		Draw(square, window);
	}

	return 0;
}


void Draw(sf::RectangleShape &squareObj, sf::RenderWindow &windowObj)
{
	windowObj.draw(squareObj);
	windowObj.display();
}

void Update(sf::RenderWindow &windowObj, sf::RectangleShape &squareObj)
{
	windowObj.clear(sf::Color::White);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{	
		windowObj.clear(sf::Color::White);
		squareObj.move(0.0f, -1.0f);
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		windowObj.clear(sf::Color::White);
		squareObj.move(-1.0f, 0.0f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		windowObj.clear(sf::Color::White);
		squareObj.move(0.0f, 1.0f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			windowObj.clear(sf::Color::White);
			squareObj.move(1.0f, 0.0f);
		}
}	
