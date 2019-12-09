#include "Spike.h"


bool Spike::collision(GameObject & otherObject)
{
	return false;
}

Spike::Spike(sf::Sprite & sprite, sf::FloatRect & rect, int width, int height)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}



Spike::Spike()
{
}


Spike::~Spike()
{
}
