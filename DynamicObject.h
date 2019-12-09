#pragma once
#include "GameObject.h"
#include "Animation.hpp"

class DynamicObject : public GameObject
{
protected:

	AnimationManager m_Anime;

	// For resetting the original position after board reset.
	sf::Vector2f m_checkPointPosition;


	sf::Vector2f m_Velocity{ 0,0 };
	sf::Vector2f m_Position{ 0,0 };

	// For now, we will only use Y - Acceleration will affect jump;
	sf::Vector2f m_Acceleration{ 0,0 };


	int m_Direction;
	int m_Speed;
	sf::Vector2f m_Center;
	sf::Clock m_Clock;
	sf::Time m_TimeElapsed;
	Texture animeTexture;
	bool m_Jumpable = false;
	bool m_Jumping = false;
	bool m_onGround = false;
	
	bool m_dead = false;
	bool isDead = false;

	

	sf::Vector2f resetPosition;
	

public:
	bool levelComplete = false;
	DynamicObject();
	virtual ~DynamicObject();

	virtual bool amIdead();
	virtual void dead(bool flag);

	virtual void setResetPosition(sf::Vector2f &position);
	sf::Vector2f getResetPosition();

	// Setters and getters for direction
	virtual void setDirection(int direction);
	virtual int getDirection();

	virtual bool isOnGround();
	virtual void onGround(bool flag);
	virtual void updateCharacter(sf::Vector2f vector, sf::Time time, int direction) = 0;
	virtual void setAccelerationY(float accel);
	virtual bool characterDead();
	virtual void reviveCharacter(bool k);
	virtual void setVelocity(sf::Vector2f velocity);
	virtual void setVelocityX(float v_X);
	virtual void setVelocityY(float v_Y);
	virtual void setAnimation(std::string action) = 0;


	virtual bool m_moveCharacter();
	//virtual bool increaseVelocity(sf::Vector2f &speed) = 0;
	virtual void animateCharacter(sf::RenderWindow &window, float time) = 0;
	virtual sf::Vector2f getVelocity();
	virtual sf::Vector2f getAcceleration();
	enum directions {
		Standing, Right, Left, Jumping
	};
};

