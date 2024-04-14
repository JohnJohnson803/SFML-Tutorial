#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Ball Shooter");
	window.setFramerateLimit(60);
	sf::Event event;

	//BALLS
	sf::CircleShape projectile;
	projectile.setFillColor(sf::Color::Red);
	projectile.setRadius(5.f);

	sf::RectangleShape enemy;
	enemy.setFillColor(sf::Color::Magenta);
	enemy.setSize(sf::Vector2f(50.f, 50.f));

	sf::CircleShape player;
	player.setFillColor(sf::Color::White);
	player.setRadius(50.f);
	player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.f);
	sf::Vector2f playerCenter;
	int shootTimer = 0;

	std::vector<sf::CircleShape> projectiles;
	projectiles.push_back(sf::CircleShape(projectile));

	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));
	
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		//UPDATE
		playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		if(shootTimer < 5)
			shootTimer++;

		player.setPosition(sf::Mouse::getPosition(window).x, window.getSize().y - player.getRadius()*2);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >=5) // Shoot 
		{
			projectile.setPosition(playerCenter);
			projectiles.push_back(sf::CircleShape(projectile));
			shootTimer = 0;
		}

		for(size_t i=0; i<projectiles.size(); i++)
		{
			projectiles[i].move(0.f, -10.f);
			if(projectiles[i].getPosition().y < 0)
				projectiles.erase(projectiles.begin() + i);
		}

		//DRAW
		window.clear();

		window.draw(player);

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