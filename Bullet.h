#pragma once
#include <iostream>
#include "DynamicObject.h"
class Bullet :
	public DynamicObject
{
public:
	Bullet();

	virtual void updateCharacter(sf::Vector2f vector, sf::Time time, int direction);
	void die();

	virtual void animateCharacter(sf::RenderWindow &window, float time);

	
	virtual void setAnimation(std::string action);

	Bullet(sf::Vector2f vec, int dir) 
	{ 
		
		int random = (rand() % 11) + 7;
		if (dir == Left)
		{
			random = -1 * random;
		}
		m_Velocity.x = float(random);
		this->m_BoundingRectangle.setPosition({ vec.x,vec.y + (this->m_BoundingRectangle.getLocalBounds().height) });
	 // this->setDirection(dir);
	  
	  // Initialize animatino
	  if (!animeTexture.loadFromFile("MegaManSheet.png")) std::cerr << "cannot open file image";


	  std::cout << "Creating shit";

	  if (!m_Anime.loadFromXML("Megaman.xml", animeTexture)) std::cerr << "cannot open file animation xml";
	  m_Anime.animList["LaserShot"].loop = 0;


	  m_Anime.set("LaserShot");
	
	 
	}
	~Bullet();
};

