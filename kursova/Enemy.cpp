#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand()%255 + 1 , rand() % 255 + 1 , rand() % 255 + 1 , 255));
}

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; //3...10
	this->speed = static_cast<float>(this->pointCount);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->type = 0;
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
