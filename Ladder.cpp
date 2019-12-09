#include "Ladder.h"


Ladder::Ladder(sf::Sprite & sprite, sf::FloatRect & rect, int width, int height)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}


Ladder::Ladder()
{
}


Ladder::~Ladder()
{
}
