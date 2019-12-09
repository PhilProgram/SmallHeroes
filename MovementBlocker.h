#pragma once
#include "StaticObject.h"
class MovementBlocker :
	public StaticObject
{
public:
	MovementBlocker(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	virtual bool intersects(GameObject &otherObject);
	MovementBlocker();
	~MovementBlocker();
};

