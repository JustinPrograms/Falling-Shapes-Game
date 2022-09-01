#include "Game.h"

// Private Functions
void Game::initVariables() {
  this->window = nullptr;

  // Game logic
  this->endGame = false;
  this->points = 0;
  this->health = 200;
  this->enemySpawnTimerMax = 20.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 5;
  this->mouseHeld = false;

}

void Game::initFonts() {
  if (!this->font.loadFromFile("Fonts/FunHouse.ttf")) {
    std::cout << "ERROR::GAME::INNITFONTS::Failed to load font!" << std::endl;
  }

}

void Game::initText() {
  this->uiText.setFont(this->font);
  this->uiText.setCharacterSize(50);
  this->uiText.setFillColor(sf::Color::White);
  this->uiText.setString("Falling Shapes");
}

void Game::initWindow() {

  this->videoMode.height = 600;
  this->videoMode.width = 800;

  this->window = new sf::RenderWindow(this->videoMode, "Falling Shapes", sf::Style::Titlebar | sf::Style::Close);

  this->window->setFramerateLimit(60);
}

// Constructors
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initFonts();
  this->initText();
}

// Destructors
Game::~Game() {

  delete this->window;

}


// Accessors

bool Game::isRunning() const {
  return this->window->isOpen();
}

bool Game::getEndGame() const {
  return this->endGame;
}


// Functions

void Game::spawnEnemy() {
  if (enemies.size() >= 5) {
    std::cout << "Max enemies reached!" << std::endl;
    return;
  }
  auto e = enemy_data[rand() % 6];
  auto enemy = enemy_t{{e.c, e.ah, e.ap, e.min, e.max}, {0, 5}, {0, 0}};
  enemy.setPosition(
      (float) (rand() % (int) (this->window->getSize().x - enemy.getSize().x)),
      0);
  this->enemies.emplace_back(enemy);
}

void Game::pollEvents() {

  // Event Polling
  while (this->window->pollEvent(this->ev)) {

    switch (this->ev.type) {
      case sf::Event::Closed:this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->ev.key.code == sf::Keyboard::Escape)
          this->window->close();
        break;
    }
  }

}

void Game::updateMousePositions() {

  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateText() {
  std::stringstream ss;
  ss << "Health: " << this->health << "\n"
     << "Points: " << this->points << std::endl;
  this->uiText.setString(ss.str());
}

void Game::updateEnemies() {

  // Updating timer for enemy_t spawning
  if (this->enemies.size() < this->maxEnemies) {

    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {

      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
  }

  // Moving and updating the enemies
  for (size_t i = 0; i < this->enemies.size(); i++) {

    bool deleted = false;
    this->enemies[i].move(this->enemies[i].accel);

    if (this->enemies[i].getPosition().y > this->window->getSize().y) {

      this->enemies.erase(this->enemies.begin() + i);

      if (this->enemies[i].getFillColor() != sf::Color::Red)
        this->health -= 1;
    }
  }

  // Check if clicked
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (!this->mouseHeld) {

      this->mouseHeld = true;
      bool deleted = false;
      for (size_t i = 0; i < this->enemies.size() && !deleted; i++)

        if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
          deleted = true;
          this->points += this->enemies[i].addPoints;
          this->health += this->enemies[i].addHealth;
          this->enemies.erase(this->enemies.begin() + i);
        }
    }
  } else {
    this->mouseHeld = false;
  }
}

void Game::update() {
  this->pollEvents();

  if (!this->endGame) {
    this->updateMousePositions();
    this->updateText();
    this->updateEnemies();
  }
  if (this->health <= 0) this->endGame = true;
}

void Game::renderText(sf::RenderTarget &target) {
  target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget &target) {
  for (auto &e: this->enemies) {
    target.draw(e);
  }
}

void Game::render() {
  this->window->clear(sf::Color(0, 0, 0, 255));
  this->renderEnemies(*this->window);
  this->renderText(*this->window);
  this->window->display();
}