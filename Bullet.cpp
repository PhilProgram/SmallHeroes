#include "Bullet.h"



Bullet::Bullet()
{

}

void Bullet::updateCharacter(sf::Vector2f vector, sf::Time time, int direction)
{
}

void Bullet::die()
{
}

void Bullet::animateCharacter(sf::RenderWindow & window, float time)
{
	m_Anime.tick(time);
	m_Anime.draw(window, (int)(m_BoundingRectangle.getPosition().x), (int)(m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height));
}

void Bullet::setAnimation(std::string action)
{
	m_Anime.set("LaserShot");
}


Bullet::~Bullet()
{
}
