#include "Wizard.h"
#include <iostream>







void Wizard::goalReach(bool flag)
{
	levelComplete = flag;
}

void Wizard::animateCharacter(sf::RenderWindow &window, float time)
{
	m_Anime.tick(time);
	m_Anime.draw(window, (int)(m_BoundingRectangle.getPosition().x), (int)(m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height));
}

void Wizard::updateCharacter(sf::Vector2f velocity, sf::Time deltaTime, int direction)
{
	
	bool jumping = false;
	// Right
	if (direction == 5)
	{
		setVelocityX(0);
	}
	if (direction == 77)
	{
		m_Anime.set("jump");
		return;
	}
	// This will update the movement when he is on ground
	if (isOnGround())
	{

		



		if (getVelocity().x == 0)
		{
			m_Anime.set("standing");
			if (getDirection() == Left){m_Anime.flip(true);}
			
		}
		if (getVelocity().x > 0)
		{
			m_Anime.set("walk");
		}
		if (getVelocity().x < 0)
		{
			m_Anime.set("walk");
			m_Anime.flip(true);
		}
		

	}
	// This is for when he is not on the ground
	/////////////////////////////////////////////////////
	// New direction is right and old direction is left? Flip is FALSE
	if (direction == Right)
	{

		if (getDirection() == Left)
		{
			m_Anime.flip(false);
		}
		setDirection(Right);
		// Debug for josh
		std::cout << 0.2*(deltaTime.asMilliseconds()) << std::endl;
		setVelocityX(0.2f*(deltaTime.asMilliseconds()));
	}
	// New direction is left and old direction is right? Flip is true
	else if (direction == Left)
	{
		if (getDirection() == Right)
		{
			m_Anime.flip(true);
		}

		setDirection(Left);
		setVelocityX(-0.2f*(deltaTime.asMilliseconds()));
	}


	// Jump
	if (direction == 3)
	{
		jumpCounter++;
		m_Anime.set("jump");
		m_Anime.play();

		if (getDirection() == Left){m_Anime.flip(true);}

		
		if (jumpCounter <= 2)
		{
			if (jumpCounter == 1)
			{
				soundJ2.play();
				setAccelerationY(velocity.y);
			}
			else
			{
				setAccelerationY(velocity.y+30);
				soundJ1.play();

				onGround(false);
				jumping = true;
			}
		}
		
	}

	if (!isOnGround() || jumping)
		setVelocityY(0.5f * deltaTime.asMilliseconds());
	jumping = false;

	//std::cout << m_DynamicObject[0]->getVelocity().y << std::endl;
	if (getAcceleration().y < 0)
	{

		onGround(false); 
		setVelocityY(getAcceleration().y / deltaTime.asMilliseconds());
		setAccelerationY(getAcceleration().y + 0.5f * deltaTime.asMilliseconds());
	}
}



Wizard::Wizard()
{
}

// Constructor - construct character based on object rectangle from level and sprite coords
Wizard::Wizard(sf::Sprite &sprite, sf::FloatRect& rect, int width, int height)
{
	if (!bufferGoal.loadFromFile("cheering.wav")) {};
	if (!bufferJ1.loadFromFile("Jump.wav")) {};
	if (!bufferSmash.loadFromFile("ItemSmash.wav")) {};
	if (!bufferJ2.loadFromFile("jumpTwo.wav")) {};
	if (!bufferCheckpoint.loadFromFile("chekpoint.wav")) {};
	if (!bufferUrg.loadFromFile("urg.wav")) {};
	if (!bufferOuch.loadFromFile("ouch.wav")) {};

	soundJ1.setBuffer(bufferJ1);
	soundJ2.setBuffer(bufferJ2);
	soundSmash.setBuffer(bufferSmash);

	checkpointSound.setBuffer(bufferCheckpoint);
	urgSound.setBuffer(bufferUrg);
	ouchSound.setBuffer(bufferOuch);
	//sound.play();

	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
	std::cout << "Our sprite: " << m_BoundingRectangle.getSize().x << " " << m_BoundingRectangle.getSize().y << std::endl;
	
	// Set acceleration and velocity to zero vector
	m_Acceleration = sf::Vector2f{ 0,0 };
	m_Velocity = sf::Vector2f{ 0,0 };

	// Initialize animatino
	if (!animeTexture.loadFromFile("MegaManSheet.png")) std::cerr << "cannot open file image";


	std::cout << "Creating shit";

	if (!m_Anime.loadFromXML("Megaman.xml", animeTexture)) std::cerr << "cannot open file animation xml";
	m_Anime.animList["jump"].loop = 0;
	//m_Anime.animList["check"].loop = 0;

	m_Anime.animList["FireBall"].loop = 0;
	m_Anime.set("walk");
}

sf::Vector2f Wizard::getCheckPosition()
{
	return resetPosition;
}

void Wizard::setCheckPosition(sf::Vector2f coords)
{
	resetPosition = coords;
}

void Wizard::m_SmashSound()
{
	soundSmash.play();
}

void Wizard::m_OuchSound()
{
	ouchSound.play();
}

void Wizard::m_UrgSound()
{
	urgSound.play();
}

void Wizard::m_checkpointSound()
{
	checkpointSound.play();
}

void Wizard::m_GoalReach()
{
	goalSound.play();
}







//// Not used.
//bool Wizard::increaseVelocity(sf::Vector2f & speed)
//{
//	return false;
//}

void Wizard::setAnim(String string)
{
	m_Anime.set(string);
}

void Wizard::setAnimation(std::string action)
{
	setAnim(action);
}

Wizard::~Wizard()
{
}

void laserGunAttack::shootLaser()
{
}
