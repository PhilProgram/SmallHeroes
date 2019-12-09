#pragma once
#include "DynamicObject.h"
class Elevator :
	public DynamicObject
{
public:

	Elevator(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);
	virtual void animateCharacter(sf::RenderWindow &window, float time);
	virtual void updateCharacter(sf::Vector2f vector, sf::Time time, int direction);
	virtual void setAnimation(std::string);
	Elevator();
	~Elevator();
};

