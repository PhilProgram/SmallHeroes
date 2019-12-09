#pragma once
#include "DynamicObject.h"
class Troll :
	public DynamicObject
{
public:

	//static constexpr double MOVEMENT_SPEED = 1.5;
	Troll(sf::Sprite &sprite, sf::FloatRect &rect, int width, int height);

	
	
	virtual void updateCharacter(sf::Vector2f vector, sf::Time time, int direction);
	void die();

	virtual void animateCharacter(sf::RenderWindow &window, float time);

	~Troll();
	virtual void setAnimation(std::string action);
};

