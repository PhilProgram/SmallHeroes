#include "Board.h"
#include "Tile.h"
#include <iostream>
#include "Wizard.h"
#include <algorithm>
#include "CollisionHandling.h"

sf::RectangleShape m_background(sf::Vector2f(500, 500));


// STL-like algorithm to run over all pairs

int previousDirection = 0;
bool jumping = false;
//template <typename FwdIt, typename Fn>
//void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
//{
//	for (; begin != end; ++begin)
//		for (FwdIt second = begin + 1; second != end; ++second)
//			fn(*begin, *second);
//}

// Randomly select if they collide or not
// In actual implementation it will check for intersection
bool collide(GameObject& objectA, GameObject& objectB)
{

	if (objectA.intersects(objectB))
	{

		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////
//					Constructor
/////////////////////////////////////////////////////////
Board::Board()
{
	
	
	//if (!gameBackground[0].loadFromFile("GreenMountain.png", sf::IntRect(0, 0, 500, 500)))
	//{
	//	std::cout << "Error loading background image" << std::endl;
	//}
	//m_background.setTexture(gameBackground);

}



void Board::createBullet(double speed)
{
	m_DynamicObject.push_back(std::make_unique<Bullet>(m_DynamicObject[0]->m_BoundingRectangle.getPosition(), m_DynamicObject[0]->getDirection()));
}

void Board::reset()
{
	m_DynamicObject.clear();
	m_StaticObject.clear();

}

bool Board::levelCompletion()
{
	if (m_DynamicObject[0]->levelComplete == true)
	{
		m_DynamicObject[0]->levelComplete = false;
		return true;

	}
	return false;
}

void Board::moveDynamics()
{
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		m_DynamicObject[i]->m_moveCharacter();
	}
}

bool Board::heroDead()
{
	if (m_DynamicObject[0]->amIdead())
	{
		return true;
	}
	return false;
}


/////////////////////////////////////////////////////////
// Update the heroes velocity, direction, and animation
/////////////////////////////////////////////////////////
void Board::updateHero(sf::Vector2f velocity, int direction, sf::Time deltaTime)
{
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		m_DynamicObject[i]->updateCharacter(velocity, deltaTime, direction);
	}
	
}
/////////////////////////////////////////////////////////
//					Check for collision
/////////////////////////////////////////////////////////
void Board::checkForCollision()
{
	// Wizard is not on ground by default unless a collision tells us otherwise.
	m_DynamicObject[0]->onGround(false);
	std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto &a) {
		std::for_each(m_StaticObject.begin(), m_StaticObject.end(), [&a](auto &b){
			
			if (collide(*a, *b))
			{
				processCollision(*a, *b);
			}
		});
	});
	std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto &a) {
		std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto &b) {

			if (a == b)
				return;
			if (collide(*a, *b))
			{
				processCollision(*a, *b);
			}
		});
	});
	
}




void Board::checkDynamics()
{
	
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		if (m_DynamicObject[i]->characterDead())
		{
			m_DynamicObject.erase(m_DynamicObject.begin() + i);
		}
	}
	//m_deadCharacters.push_back(std::move(m_DynamicObject[0]));
}

/////////////////////////////////////////////////////////
//					Update the camera
/////////////////////////////////////////////////////////
void Board::updateView(sf::RenderWindow & window, sf::Vector2f & velocity)
{
	// Check if hes not deadif (!m_DynamicObject[0]->amIdead())
	
	//window.draw(m_background);
	
		my_Camera.setPosition(m_DynamicObject[0]->m_BoundingRectangle.getPosition());
	

	// Main character has died.
	
		//control.displayMainMenu(window);
	
}
/////////////////////////////////////////////////////////
//					Set camera, draw animation
/////////////////////////////////////////////////////////
void Board::m_Update(float &time, sf::RenderWindow & window)
{	
	//window.draw(m_DynamicObject[0]->m_BoundingRectangle);
	my_Camera.SetView(window);	

	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		//window.draw(m_DynamicObject[i]->m_BoundingRectangle);
		m_DynamicObject[i]->animateCharacter(window, time);
	}
	
}
///////////////////////////////////////////////////////////
//					Initialize objects
/////////////////////////////////////////////////////////
void Board::initiateBoard(vector<std::unique_ptr<DynamicObject>> &Dynamicobjects, vector<std::unique_ptr<StaticObject>> &Staticobjects)
{
	
	
	m_DynamicObject = std::move(Dynamicobjects);
	m_StaticObject = std::move(Staticobjects);
}
// Hero animation function
// Set up a timer, and set animation to death for a few seconds
// Display center console screen press Enter to continue
// Increase death counter
// 
void Board::heroDeathAnimation(sf::RenderWindow & window)
{
	// Animation timer
	sf::Clock clock;
	sf::Clock timer;
	timer.restart();


	m_DynamicObject[0]->setAnimation("jump");
	do
	{
		float time = (float)(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / 500;
		if (time > 40) time = 40;
		m_DynamicObject[0]->animateCharacter(window, time);

	} while (timer.getElapsedTime().asSeconds() < 5.0f);
	

	


	



	m_DynamicObject[0]->dead(false);
	//std::system("pause");
}


Board::~Board()
{
	
}
