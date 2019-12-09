#pragma once
#include "SFML\Graphics.hpp"
class GameObject
{
public:

	

	// If needed
	sf::Color m_color;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	// Very important - bounds the object and is used for collision
	sf::RectangleShape m_BoundingRectangle;



	// Check intersect of sprites( bounding rectangles )
	virtual bool intersects(GameObject &otherObject);
	

	
	virtual ~GameObject();
};

