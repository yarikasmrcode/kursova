#include "Game.h"


void Game::initWindow()
{
	//create window
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "3CY",
		sf::Style::Close);

	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//load font
	if (!this->font.loadFromFile("Fonts/Pacifico.ttf")) {
		std::cout << "could not load font ";
	}

	//init point text
	this->pointText.setPosition(620, 20);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::Yellow);
	this->pointText.setString("SLAVA UKRAINE");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER, KOZAk :/");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f 
	  - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f
	  - this->gameOverText.getGlobalBounds().height / 2.f);

	//init playetGUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::Black);
}
 
void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/background.png")) {
		std::cout << "ERROR could not load background texture";
	}
	this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
	this->initWorld();
	this->initSystems();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	for (auto& i : this->textures)
	{
		delete i.second; //delete second part of the container i.g. texture
	}

	//delete bullets
	for (auto*i : this->bullets)
	{
		delete i;
	}

	//delete enemies
	for (auto*i : this->enemies) {
		delete i;
	}
}

//functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePullEvents();
		if (this->player->getHp() > 0) {
			this->update();
		}
		this->render();
	}
}

void Game::updateGUI()
{
	std::stringstream sStream;
	sStream << "moskaliv killed : " << this->points;
	this->pointText.setString(sStream.str());

	//update player gui
	float hpPercent = static_cast<float>(this->player->getHp())
		/ this->player->getHpMax();

	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,
		this->playerHpBar.getSize().y));
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::updatePullEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& this->player->canAttack())
	{
		//add to vector
		this->bullets.push_back(new Bullet(this->textures["BULLET"], 
			this->player->getPosition().x + this->player->getBounds().width / 2.f,
			this->player->getPosition().y,
			0.f,-1.f,5.f));
	}
}

void Game::updateBullet()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet remove when touch top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0)
		{
			//delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter); //iterator to beginning + counter
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning

	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand()% this->window->getSize().x
			- 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//bullet remove when touch top of screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delete the enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//enemy player collision
		else if(enemy->getBounds().intersects(this->player->getBounds())) {
			this->player->looseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i) {
		bool enemyDeleted = false;
		for (size_t k = 0; k < this->bullets.size() && !enemyDeleted; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) {
				
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);				

				enemyDeleted = true;
			}
		}
	}
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	//left
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//top
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0);
	}
	//bottom
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::update()
{
	//move player
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateBullet();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::render()
{
	this->window->clear(); //clear the old frame

	//draw world backgroud
	this->renderWorld();

	//draf stuff in here
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//game over screen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}

	this->window->display(); //display what's drawn

}
