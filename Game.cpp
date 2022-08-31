#include "Game.h"


// Private Functions
void Game::initVariables() {

	this->window = nullptr;

    // Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
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

void Game::initEnemies() {

    this->enemy.setPosition(50.f, 50.f);
    this->enemy.setSize(sf::Vector2f(100, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
}



// Constructors
Game::Game() {
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

// Destructors
Game::~Game() {

	delete this->window;

}


// Accessors

const bool Game::isRunning() const {
	return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}


// Functions

void Game::spawnEnemy() {

    // Spawns enemy
    this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

    
    // Randomize enemy type
    int type = rand() % 6;
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));

    float sizeFloat = static_cast<float>(rand() % 10) / 9.f;
    sf::Vector2f size = sf::Vector2f(sizeFloat, sizeFloat);


    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(1.f, 1.f));

    switch (type) {
    case 0:
        this->enemy.setScale(sf::Vector2f(0.10f, 0.10f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color(255, 165, 0, 255));
        break;
    case 4:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color::Green);
        break;
    case 5:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color::Red);
        break;
    default:
        this->enemy.setScale(size);
        this->enemy.setFillColor(sf::Color::Yellow);
        break;

    }
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {

    // Event Polling
    while (this->window->pollEvent(this->ev)) {

        switch (this->ev.type) {

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

    // Updating timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {

        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {

            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }
    }

    // Moveing and updating the enemies
    for (int i = 0; i < this->enemies.size(); i++) {

        bool deleted = false;
        this->enemies[i].move(0.f, 5.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {

            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    // Check if clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {

            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)

                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

                    deleted = true;

                    if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
                        this->points += 10;
                        this->health += 5;
                    } 
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
                        this->points += 5;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
                        this->points += 3;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color(255, 165, 0, 255)) {
                        this->points += 2;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Green) {
                        this->points += 1;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Red) {
                        this->points -= 100;
                        this->health -= 100;
                    }

                    this->enemies.erase(this->enemies.begin() + i);
                }
        }
    }
    else {
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
    if (this->health <= 0)
        this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {

    for (auto& e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {

    // Renders all objects

    this->window->clear(sf::Color(0, 0, 0, 255));

    // Drawing game objects
    this->renderEnemies(*this->window);


    this->renderText(*this->window);


    this->window->display();
}

