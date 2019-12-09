#pragma once
#include "StaticObject.h"
class Tile :
	public StaticObject
{
public:
	Tile(sf::Sprite &sprite, sf::FloatRect &rect,int width, int height);
	virtual ~Tile();
	virtual bool intersects(GameObject &otherObject);
	
};

