#pragma once

#include "Animation.hpp"
class Camera
{
private:
	sf::View view;
public:
	Camera();
	~Camera();
	void MoveView(sf::Vector2f &coords);
	void setPosition(const sf::Vector2f &coords);
	void SetView(sf::RenderWindow& window);
	const sf::Vector2f& GetCenter(void) const;
};

