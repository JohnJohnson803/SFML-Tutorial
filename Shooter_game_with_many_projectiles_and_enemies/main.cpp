#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640,480), "Ball Shooter");
	sf::Event event;

	//Balls
	sf::CircleShape projectile;
	projectile.setFillColor(sf::Color::Red);
	projectile.setRadius(5.f);

	sf::CircleShape projectile2;
	projectile2.setFillColor(sf::Color::Red);
	projectile2.setRadius(5.f);

	sf::RectangleShape enemy;
	enemy.setFillColor(sf::Color::Magenta);
	enemy.setSize(sf::Vector2f(50.f, 50.f));
	
	sf::CircleShape player;
	player.setFillColor(sf::Color::White);
	player.setRadius(50.f);
	player.setPosition((window.getSize().x / 2) - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10);

	sf::Vector2f playerCenter;

	std::vector<sf::CircleShape> projectiles;
	projectiles.push_back(projectile);


	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(enemy);


	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		} 
		
		//UPDATE
		playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			
		}
		
		//DRAW

		window.clear();
		window.draw(player);
		window.draw(projectile2);

		for(size_t i=0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

		for(size_t i=0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}
		
		window.display();
	}

	return 0;
}
