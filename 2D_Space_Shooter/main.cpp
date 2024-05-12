#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib>

class Player
{
    public:
    sf::Sprite player;
    int MaxHP = 20;
    int HP;

    Player(sf::Texture &texture)
    {
        this->player.setTexture(texture);
        this->player.setScale(0.2f, 0.2f);
        this->HP = this->MaxHP;
    }

    ~Player(){};

};

class Bullet
{
    public:
    sf::Sprite bullet;

    Bullet(sf::Texture &texture, const Player &playerPosition)
    {
        this->bullet.setTexture(texture);
        this->bullet.setScale(0.09, 0.09);

        //Calculates Player's centerposition
        this->bullet.setPosition(playerPosition.player.getPosition().x + playerPosition.player.getGlobalBounds().width / 2, playerPosition.player.getPosition().y + playerPosition.player.getGlobalBounds().height / 2);
    }

    ~Bullet(){};
};

class Enemy 
{
    public:
    sf::Sprite enemy;

    Enemy(sf::Texture &texture, sf::RenderWindow &windowSize)
    {
        this->enemy.setTexture(texture);
        this->enemy.setScale(0.2, 0.2);
        //this->enemy.setPosition(windowSize.getSize().x + this->enemy.getGlobalBounds().width, rand()%windowSize.getSize().y - this->enemy.getGlobalBounds().height);
        int maxY = rand()%windowSize.getSize().y - this->enemy.getGlobalBounds().height;

        if(maxY > 0 )
        {
            this->enemy.setPosition(windowSize.getSize().x + this->enemy.getGlobalBounds().width, maxY);
        }

        else{
            this->enemy.setPosition(windowSize.getSize().x + this->enemy.getGlobalBounds().width, 0);
        }
    }
};

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1280,720), "2D Space Shooter");
    window.setFramerateLimit(60);
    sf::Event event;

    //Create Player Texture 
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/ship.png");
    //Initialize Player object
    Player p1(playerTexture);
    //Playet ShootTimer 
    int shootTimer = 0;
    //Player Healthbar
    sf::RectangleShape healthBar;
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setSize(sf::Vector2f(p1.player.getGlobalBounds().width, 10.f));

    //Create Bullet Texture
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("textures/missileTex01.png");
    //Create Vector container to hold bullets
    std::vector<Bullet> projectiles;

    //Enemy
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("textures/enemy1.png");
    Enemy enemy1(enemyTexture, window);
    std::vector<Enemy> enemies;
    int enemySpawnTimer = 0;


    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Clears the screen 
        window.clear();

        //Player Movement 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Move player up
            p1.player.move(0.f, -5.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Move player down
            p1.player.move(0.f, 5.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Move player left
            p1.player.move(-5.f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Move player right
            p1.player.move(5.f, 0);
        
        healthBar.setPosition(p1.player.getPosition().x, p1.player.getPosition().y + p1.player.getGlobalBounds().height + 30);
        std::cout << (p1.player.getGlobalBounds().width) << std::endl;
        

        //Player movement domain
        if(p1.player.getPosition().y <= 0) // Top Border
            p1.player.setPosition(p1.player.getPosition().x, 0);

        if(p1.player.getPosition().y + p1.player.getGlobalBounds().height >= window.getSize().y) // Bottom Border
            p1.player.setPosition(p1.player.getPosition().x, window.getSize().y - p1.player.getGlobalBounds().height);

        if(p1.player.getPosition().x <=0) //Left Border
            p1.player.setPosition(0, p1.player.getPosition().y);

        if(p1.player.getPosition().x + p1.player.getGlobalBounds().width >= window.getSize().x) // Right Border
            p1.player.setPosition(window.getSize().x - p1.player.getGlobalBounds().width, p1.player.getPosition().y);


        //Player Missile Cooldown timer
        if(shootTimer < 20)
        {
            shootTimer++;
        }
        
        // Player Missile Projectiles
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 20)
        {
            projectiles.push_back(Bullet(bulletTexture, p1));
            shootTimer = 0;
        }

        //Moving Player Missile Projectiles
        for(auto it = projectiles.begin(); it != projectiles.end(); it++)
        {
            it->bullet.move(30.f, 0);
        }

        //Projectile Collision with Border
        for(auto it = projectiles.begin(); it != projectiles.end();)
        {
            if(it->bullet.getPosition().x >= window.getSize().x)
                {
                   it = projectiles.erase(it);
                }

            else{
                it++;
            }
        }

        //Creating enemies
        if(enemySpawnTimer < 50)
        {
            enemySpawnTimer++;
        }

        if(enemySpawnTimer >= 50)
            {
                enemies.push_back(Enemy(enemyTexture, window));
                enemySpawnTimer = 0;
            }
        //Moving Enemies across the window
        for(auto it = enemies.begin(); it != enemies.end(); it++)
        {
            it->enemy.move(-10.f, 0);
        }

        //Enemy collision with window border
        for(auto it = enemies.begin(); it != enemies.end();)
        {
            if(it->enemy.getPosition().x < 0 - p1.player.getGlobalBounds().width)
            {
                it = enemies.erase(it);
            }
            else{
                it++;
            }
        }

        //Enemy Collision with Player
        for(auto it = enemies.begin(); it != enemies.end();)
        {   
            if(p1.player.getGlobalBounds().intersects(it->enemy.getGlobalBounds()))
            {
                enemies.erase(it);
            }
        
            else{
                it++;
            }
        }

        //Enemy Collision with Missile
        for(auto it1 = enemies.begin(); it1 != enemies.end();)
         {
            for(auto it2 = projectiles.begin(); it2 != projectiles.end();)
                {
                    if(it1->enemy.getGlobalBounds().intersects(it2->bullet.getGlobalBounds()))
                        {
                            it2 = projectiles.erase(it2);
                            it1 = enemies.erase(it1);
                            break;
                        }
                    else{
                        it2++;
                    }
                }

                if (it1 != enemies.end()) {
                    it1++;  // Only increment it1 if it has not been erased
    }
         }

        //Drawing Player Missile Projectiles
        for(auto it = projectiles.begin(); it != projectiles.end(); it++)
        {
            window.draw(it->bullet);
        }

        // Drawing enemies
        for(auto it = enemies.begin(); it != enemies.end(); it++)
        {
            window.draw(it->enemy);
        }
        
        window.draw(p1.player);
        window.draw(healthBar);
        window.display();
    }

    return 0;
}