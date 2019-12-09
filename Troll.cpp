#include "Troll.h"
#include<iostream>
enum directions { Right, Left };

Troll::Troll(sf::Sprite &sprite, sf::FloatRect& rect, int width, int height)
{
	int random = (rand() % 3) + 1;
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
	std::cout << "Our sprite: " << m_BoundingRectangle.getSize().x << " " << m_BoundingRectangle.getSize().y << std::endl;

	if (!animeTexture.loadFromFile("Troll.PNG")) std::cerr << "cannot open file imagePPPPPPPPPPP";

	if (!m_Anime.loadFromXML("NewTrollAnimation.xml", animeTexture)) std::cerr << "cannot open LELEL animation xml";
	m_Anime.set("Walk");

	
	m_Velocity.x = float(random);
	setDirection(Left);
	
}

void Troll::updateCharacter(sf::Vector2f vector, sf::Time time, int direction)
{
	if (getVelocity().x > 0)
	{
		m_Anime.set("Walk");
		m_Anime.flip(true);
	}
	if (getVelocity().x < 0)
	{
		m_Anime.set("Walk");
		
	}
}
void Troll::animateCharacter(sf::RenderWindow &window, float time)
{
	m_Anime.tick(time);
	m_Anime.draw(window, (int)(m_BoundingRectangle.getPosition().x), (int)(m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height));
}

void Troll::die()
{
	m_Anime.set("Die");
	setVelocityX(-1);
}
Troll::~Troll()
{
}

void Troll::setAnimation(std::string action)
{
	m_Anime.set(action);
}
