#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <sstream>
#include<map>

class Game {

private:
	//window
	sf::RenderWindow* window;

	//resources
	std::map<std :: string, sf::Texture*> textures; // "key-value"
	std::vector<Bullet*> bullets; //instead of dynamic array

	//player
	Player* player;

	//player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//enemies
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTexture;
	sf::Text gameOverText;
	unsigned points;

	//private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//functions
	void run();
	
	void updateGUI();
	void renderGUI();
	void renderWorld();
	void updatePullEvents();
	void updateInput();
	void updateBullet();
	void updateEnemies();
	void updateCombat();
	void updateWorld();
	void updateCollision();
	void update(); //logic
	void render(); //draws the staff
};