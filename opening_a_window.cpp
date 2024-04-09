#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void Draw(sf::RenderWindow &windwoObj, sf::CircleShape &circleObj);
void moveLeft(sf::CircleShape &circleObj);
void moveRight(sf::CircleShape &circleObj);
void moveUp(sf::CircleShape &circleObj);
void moveDown(sf::CircleShape &circleObj);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,400),"Game Window");
	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(100);
	sf::Event event;

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				moveLeft(circle);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				moveRight(circle);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
				moveUp(circle);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
				moveDown(circle);
		}	

		window.clear();
		Draw(window, circle);
	}

	return 0;
}

void Draw(sf::RenderWindow &windowObj, sf::CircleShape &circleObj)
{
	windowObj.draw(circleObj);
	windowObj.display();
}
void moveLeft(sf::CircleShape &circleObj)
{
	circleObj.move(-1.0f, 0.0f);
}

void moveRight(sf::CircleShape &circleObj)
{
	circleObj.move(1.0f, 0.0f);
}

void moveUp(sf::CircleShape &circleObj)
{
	circleObj.move(0.0f, -1.0f);
}

void moveDown(sf::CircleShape &circleObj)
{
	circleObj.move(0.0f, 1.0f);

}


