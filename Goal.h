#pragma once
#include "StaticObject.h"
class Goal :
	public StaticObject
{
public:
	Goal(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	virtual ~Goal();
	virtual bool intersects(GameObject &otherObject);
};

