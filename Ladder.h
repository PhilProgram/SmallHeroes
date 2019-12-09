#pragma once
#include "StaticObject.h"
class Ladder :
	public StaticObject
{
public:

	Ladder(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	Ladder();
	~Ladder();
};

