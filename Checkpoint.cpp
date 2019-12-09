#include "Checkpoint.h"
#include <iostream>




void Checkpoint::setCheckpoint(bool flag)
{
	activeCheckpoint = flag;
}

bool Checkpoint::checkPointActive()
{
	return activeCheckpoint;
}

Checkpoint::Checkpoint(sf::Sprite & sprite, sf::FloatRect & rect, int width, int height)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
	if(!m_texture.loadFromFile("checkp.PNG") )
		std::cout << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	m_sprite.setTexture(m_texture);
	//increase checkpoint counter
}

Checkpoint::Checkpoint()
{
	std::cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFk";
}


Checkpoint::~Checkpoint()
{
}
