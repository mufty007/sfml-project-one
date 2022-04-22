#include "Game.h"


//private functions

void Game::initializeVariables()
{
	this->window = nullptr;

	this->points = 0;
	this->enemySpawnTimerMax = 15.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 15;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	//window size
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "SFML First Game", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
}

void Game::initEnemeies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Black);
	this->enemy.setOutlineThickness(1.f);

	

}

//Consructors / Destructors

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initEnemeies();
}


Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}



// Functions


void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets thier colors and positions
		- Sets a random position
		- Sets a random color
		- Adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
		0.f
	);

	this->enemy.setFillColor(sf::Color::Yellow);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);

	//Remove enemies at the end of screen
}

void Game::pollevents()
{
	//Event polling
	while(this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateEnemies()
{
	/*
		@return void
		
		Updating the enemy spawn timer and spawn enemies
		when the total amonut of enemies is smaller than the max.
		Moves the emenies downwords
		Removes the enemies at the end of the sccreen
	*/

	//Updating the timer for enemy spawning

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 2.f);

		//if enemy pass the bottom of screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
			this->enemies.erase(this->enemies.begin() + i);
	}


	//Checked if enemy is cicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld = false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//delete  the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain points
					this->points += 1.f;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		//Render enemies
		this->window->draw(e);
	}
}

void Game::updateMousePositions()
{
	/*
		@ return void

		Updates the mouse positions:
		- Mounse position relative to window
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollevents();

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::render()
{

	/*
		* @return void
		* 
		- clear window
		- render object
		- display frame in window
		- render game objects
	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->window->display();
}
