#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float speed)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.2f, 0.5f);

	this->direction.x = dirX;
	this->direction.y = dirY;
	this->shape.setPosition(posX, posY);
	this->speed = speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//movement
	this->shape.move(this->speed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
