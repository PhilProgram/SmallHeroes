#pragma once
#include "DynamicObject.h"
#include <SFML/Audio.hpp>
#include <thread> 






// AttackType object
class AttackType
{
public:
	virtual void Attack() = 0;
};


// Laser Attack
class laserGunAttack : public AttackType
{
public:
	void shootLaser();
	void Attack()
	{
		//std::thread tt(shootLaser(void));
		// Create a new Thread!
		// Laser Gun Shot
		// Create sprite on the side of where hes facing , 
		// Set the velocity, direction and speed of object
		// Add it to the vector


		// Handle collestion of the shot if it collides. 

	}
};








class Wizard :
	public DynamicObject
{
	

protected:
	
	sf::SoundBuffer bufferJ1;
	sf::SoundBuffer bufferJ2;
	sf::SoundBuffer bufferSmash;

	sf::SoundBuffer bufferUrg;
	sf::SoundBuffer bufferOuch;
	sf::SoundBuffer bufferCheckpoint;

	sf::SoundBuffer bufferGoal;

	sf::Sound goalSound;
	sf::Sound checkpointSound;
	sf::Sound soundJ1;
	sf::Sound soundJ2;
	sf::Sound soundSmash;
	sf::Sound ouchSound;
	sf::Sound urgSound;
	
	
	
public:
	void goalReach(bool flag);
	int jumpCounter = 0;
	virtual void animateCharacter(sf::RenderWindow &window, float time);
	virtual void updateCharacter(sf::Vector2f vector, sf::Time time, int direction);
	


	Wizard();
	Wizard(sf::Sprite &sprite, sf::FloatRect &rect,int width, int height);

	sf::Vector2f getCheckPosition();
	void setCheckPosition(sf::Vector2f coords);
	//void setCheckpoint(int i); 
	bool jumpFlag = true;
	void setAnim(String);
	virtual void setAnimation(std::string action);
	// Sounds
	void m_SmashSound();
	void m_OuchSound();
	void m_UrgSound();
	void m_checkpointSound();
	void m_GoalReach();
	
	virtual ~Wizard();
};

