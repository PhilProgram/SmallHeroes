#pragma once
#include "StaticObject.h"
class Checkpoint :
	public StaticObject
{
protected: 
	bool activeCheckpoint = false;
public:
	void setCheckpoint(bool flag);
	bool checkPointActive();
	Checkpoint(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	Checkpoint();
	~Checkpoint();
};

