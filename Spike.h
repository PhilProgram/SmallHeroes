#pragma once
#include "StaticObject.h"
class Spike :
	public StaticObject
{
public:
	virtual bool collision(GameObject & otherObject);
	Spike(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	Spike();
	~Spike();
};

