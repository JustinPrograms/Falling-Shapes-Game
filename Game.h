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
#include "enemy.h"

/*
	Game engine / Wrapper Class
*/

class Game {

 private:

  // Variables
  // Window
  sf::RenderWindow *window;
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
  long long points;
  long long health;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld;

  // Game objects
  std::vector<enemy_t> enemies;

  // Private Functions
  void initVariables();
  void initWindow();
  void initFonts();
  void initText();

 public:

  enemy_data_t enemy_data[6] = {
      {sf::Color::Magenta, 1, 4, 2, 2},
      {sf::Color::Blue, 1, 4, 2, 2},
      {sf::Color::Cyan, 1, 4, 2, 2},
      {sf::Color(255, 165, 0, 255), 1, 4, 2, 2},
      {sf::Color::Green, 1, 4, 2, 2},
      {sf::Color::Red, -100, -100, 2, 2},
  };

  // Constructors
  Game();
  // Destructors
  virtual ~Game();

  // Accessors
  bool isRunning() const;
  bool getEndGame() const;

  // Functions
  void spawnEnemy();

  void pollEvents();
  void updateMousePositions();
  void updateText();
  void updateEnemies();
  void update();

  void renderText(sf::RenderTarget &target);
  void renderEnemies(sf::RenderTarget &target);
  void render();

};