#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
	int dir = 0;

	sf::RenderWindow window(sf::VideoMode(640,480), "Simple Game");
	window.setFramerateLimit(60);	
	sf::CircleShape hoop;
	hoop.setRadius(50.f);
	hoop.setFillColor(sf::Color::Black);
	hoop.setOutlineThickness(2.f);
	hoop.setOutlineColor(sf::Color::Blue);

	sf::CircleShape ball;
	ball.setRadius(30);
	ball.setPosition(0, window.getSize().y - ball.getRadius() * 3);
	ball.setFillColor(sf::Color::Red);

	while(window.isOpen())
		{
			sf::Event event;
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
					window.close();
			}

			//Update hoop
			if(hoop.getPosition().x <= 0)
			{
				dir = 1;
			}

			else if(hoop.getPosition().x + hoop.getRadius()*2 >= window.getSize().x) 
			{
				dir = 0;
			}

			if(dir == 1)
			{
				hoop.move(5.f,0);
			}

			else if (dir == 0)
			{
				hoop.move(-5.f,0);
			}

			//Update Ball
			ball.setPosition(sf::Mouse::getPosition(window).x, window.getSize().y - ball.getRadius() * 3);

			window.clear(sf::Color::White);

			//Draw  
			window.draw(hoop);
			window.draw(ball);
			window.display();
		}
	return 0;
}
