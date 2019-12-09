#include "Goal.h"





Goal::Goal(sf::Sprite & sprite, sf::FloatRect & rect, int width, int height)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}

Goal::~Goal()
{
}

bool Goal::intersects(GameObject & otherObject)
{
	if (m_sprite.getGlobalBounds().intersects(otherObject.m_sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}
