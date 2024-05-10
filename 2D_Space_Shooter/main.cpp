#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>

class Player
{
	public:
		sf::Sprite player;

		Player(sf::Texture *texture)
		{
			this->player.setTexture(*texture);
			this->player.setScale(0.2, 0.2);
			this->player.setRotation(360);

		}

		~Player(){};
};

class Bullet
{
	public:
	sf::Sprite bullet;

	Bullet(sf::Texture *texture, const Player &playerPosition)
	{	
		this->bullet.setTexture(*texture);
		this->bullet.setScale(0.1f, 0.1f);
		this->bullet.setPosition(playerPosition.player.getPosition().x + (playerPosition.player.getGlobalBounds().width / 2), playerPosition.player.getPosition().y + (playerPosition.player.getGlobalBounds().height / 2));
	}

	~Bullet(){};
};

class Enemy
{
	public:
		sf::Sprite enemy;
		
		Enemy(sf::Texture *texture, sf::Vector2u windowSize)
		{
			this->enemy.setTexture(*texture);
			this->enemy.setScale(0.2, 0.2);

			this->enemy.setPosition(windowSize.x, rand() % (windowSize.y - static_cast<int>(this->enemy.getGlobalBounds().height)));
			
		}
		~Enemy(){};
};

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1920,1080),"Space Shooter");
	window.setFramerateLimit(60);
	sf::Event event;

	//Texture Init
	//Player Texture
	sf::Texture playerTexture;
	playerTexture.loadFromFile("textures/ship.png");
	Player p1(&playerTexture);

	//Enemy
	//Texture
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("textures/enemy1.png");
	std::vector<Enemy> enemies;
	enemies.push_back(Enemy(&enemyTexture, window.getSize()));
	int enemyTimer = 20;

	//Bullet 
	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("textures/missileTex01.png");
	std::vector<Bullet> missles;

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		//Player Movement 
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			p1.player.move(0, -5.f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			p1.player.move(0, 5.f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			p1.player.move(-5.f, 0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			p1.player.move(5.f, 0);

		window.clear();

		//Firing Missle
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				missles.push_back(Bullet(&bulletTexture, p1));
			}
		
		//Player collision with window borders
		if(p1.player.getPosition().x <= 0) //Left border of the window
			p1.player.setPosition(0, p1.player.getPosition().y);

		if(p1.player.getPosition().x + p1.player.getGlobalBounds().width >= window.getSize().x) //Right border of the window 
			p1.player.setPosition(window.getSize().x - p1.player.getGlobalBounds().width, p1.player.getPosition().y);
		
		if(p1.player.getPosition().y <= 0) //Top bprder of the window
			p1.player.setPosition(p1.player.getPosition().x, 0);
		
		if(p1.player.getPosition().y + p1.player.getGlobalBounds().height >= window.getSize().y) //Bottom of the window
			p1.player.setPosition(p1.player.getPosition().x, window.getSize().y - p1.player.getGlobalBounds().height);
		
		
		
		//Enemy 
		//Enemy Spawn Timer
		if(enemyTimer <= 100)
		{
			enemyTimer++;
		}

		if(enemyTimer >= 100)
		{
			enemies.push_back(Enemy(&enemyTexture, window.getSize()));
			enemyTimer = 0;
		}

		//Drawing and Moving enemies
		for(size_t i=0; i<enemies.size();)
		{
			enemies[i].enemy.move(-5.f, 0);
			window.draw(enemies[i].enemy);
			//Enemy Collision with border and player 
			if(enemies[i].enemy.getPosition().x + enemies[i].enemy.getGlobalBounds().width <= 0 || enemies[i].enemy.getGlobalBounds().intersects(p1.player.getGlobalBounds()))
				enemies.erase(enemies.begin() + i);
				else{
					i++;
				}
		}

		for(size_t i=0; i<missles.size();)
		{
			missles[i].bullet.move(20.f, 0);
			window.draw(missles[i].bullet);
			if(enemies[i].enemy.getGlobalBounds().intersects(missles[i].bullet.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				missles.erase(missles.begin() + i);
			}

			else{
				i++;
			}
		}

		
		window.draw(p1.player);
		window.display();
	}

	return 0;
}
