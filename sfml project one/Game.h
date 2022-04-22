#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
 This class acts as the game engine.
 wrapper class
 /*/


class Game
{

private:
	// Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	// Game objeccts
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


	// private functions
	void initializeVariables();
	void initWindow();
	void initEnemeies();

public:

	//Consructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemy();

	void pollevents();

	void updateEnemies();
	void renderEnemies();
	void updateMousePositions();
	void update();
	void render();

};

