#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Game engine / Wrapper Class
*/ 





class Game {

private: 

	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game logic
	bool endGame;
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;




	// Private Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();


public:

	// Constructors
	Game(); 
	// Destructors
	virtual ~Game(); 


	// Accessors
	const bool isRunning() const;
	const bool getEndGame() const;


	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();

};

class EnemyTest {

private:

	std::string colors[6] = {"MAGENTA", "BLUE", "CYAN", "ORANGE", "GREEN", "RED" };

	int pointsAssociatedColors[6] = { 10, 5, 3, 2, 1, -100 };
	int HealthAssociatedColors[6] = { 5, 1, 0, 0, 0, -100 };


	int sizee;
	std::string color;
	int speed;
	int addPoints;
	int addHealth;

public:
	sf::RectangleShape spawnEnemyTest();


};
