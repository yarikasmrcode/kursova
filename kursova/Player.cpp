#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 12.f;
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//load a texture from a file
	if (!this->texture.loadFromFile("Textures/Player.png"))
	{
		std::cout << "some went wrong my man";
	}
}

void Player::initSprite()
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(0.4f, 0.4f);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player()
{ 
}

sf::Vector2f Player::getPosition()
{
	return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds()
{
	return this->sprite.getGlobalBounds();
}

int Player::getHp() 
{
	return this->hp;
}

int Player::getHpMax()
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHP(const int hp)
{
	this->hp = hp;
}

void Player::looseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.5f;
		return true;
	}

	return false;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

//functions
void Player::update()
{
	this->updateAttack();
}

void Player::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
	{
		this->attackCoolDown += 1.f;
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hp <= 0) {
		if (!this->texture.loadFromFile("Textures/playerDead.png"))
		{
			std::cout << "some went wrong my man";
		}
		this->sprite.setTexture(this->texture);
	}
}
