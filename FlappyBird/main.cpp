#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
	sf::Event event;

	while(window.isOpen())
	{
		//handle events
		

		//update game logic
		

		//draw
		window.clear();

		//draw SFML objects

		window.display();
	}
	return EXIT_SUCCESS;
}
