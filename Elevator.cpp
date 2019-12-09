#include "Elevator.h"
#include <iostream>


Elevator::Elevator(sf::Sprite &sprite, sf::FloatRect& rect, int width, int height)
{

	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
	std::cout << "Our sprite: " << m_BoundingRectangle.getSize().x << " " << m_BoundingRectangle.getSize().y << std::endl;
	if (!animeTexture.loadFromFile("Wall.PNG")) std::cerr << "cannot open file imagePPPPPPPPPPP";
	
	if (!m_Anime.loadFromXML("Elevator.xml", animeTexture)) std::cerr << "cannot open file animation xml";
	m_Anime.set("move");
	
	
	m_Velocity.x = -0.5f;
	setDirection(Left);

}

void Elevator::updateCharacter(sf::Vector2f vector, sf::Time time, int direction)
{
	if (getVelocity().x > 0)
	{
		m_Anime.set("move");
	
	}
	if (getVelocity().x < 0)
	{
		m_Anime.set("move");

	}
}

void Elevator::setAnimation(std::string)
{
}

void Elevator::animateCharacter(sf::RenderWindow &window, float time)
{
	m_Anime.tick(time);
	m_Anime.draw(window, (int)(m_BoundingRectangle.getPosition().x), (int)(m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height));
}


Elevator::Elevator()
{
}


Elevator::~Elevator()
{
}
