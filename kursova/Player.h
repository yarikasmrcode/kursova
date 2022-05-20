#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Player
{
private:

	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;
	float attackCoolDown;
	float attackCoolDownMax;

	int hp;
	int hpMax;

	//private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//accessor
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	int getHp();
    int getHpMax();

	//modifier
	void setPosition(const sf :: Vector2f pos);
	void setPosition(const float x, const float y);
	void setHP(const int hp);
	void looseHp(const int value);

	//fuctions
	const bool canAttack();
	void move(const float dirX, const float dirY);
	void update();
	void updateAttack();
	void render(sf::RenderTarget& target);
};

