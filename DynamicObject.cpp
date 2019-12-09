#include "DynamicObject.h"


bool DynamicObject::amIdead()
{
	return m_dead;
}

void DynamicObject::dead(bool flag)
{
	m_dead = flag;
}

void DynamicObject::setResetPosition(sf::Vector2f & position)
{
	resetPosition = position;
}

sf::Vector2f DynamicObject::getResetPosition()
{
	return resetPosition;
}
DynamicObject::DynamicObject()
{
}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::updateCharacter(sf::Vector2f vector, sf::Time time, int direction)
{

}
// Set the Y acceleration ( for jumps )
void DynamicObject::setAccelerationY(float accel)
{
	m_Acceleration.y = accel;
}
bool DynamicObject::characterDead()
{
	return isDead;
}
void DynamicObject::reviveCharacter(bool trigger)
{
	isDead = trigger;
}
// Get the current (X Y) velocity
sf::Vector2f DynamicObject::getVelocity()
{
	return m_Velocity;
}
// Get the current acceleration
sf::Vector2f DynamicObject::getAcceleration()
{
	return m_Acceleration;
}
// Set velocity of x
void DynamicObject::setVelocityX(float  v_X)
{
	m_Velocity.x = v_X;
}
// Set velocity of y
void DynamicObject::setVelocityY(float  v_Y)
{
	m_Velocity.y = v_Y;
}

// Set the velocity
void DynamicObject::setVelocity(sf::Vector2f  velocity)
{
	m_Velocity = velocity;
}
// Get the current direction ( state )
int DynamicObject::getDirection()
{
	return m_Direction;
}
// Check wether we are on ground
bool DynamicObject::isOnGround()
{
	return m_onGround;
}
// Set the on ground falg to true
void DynamicObject::onGround(bool flag)
{
	m_onGround = flag;
}
// Move the character according to the velocity
bool DynamicObject::m_moveCharacter()
{
	m_BoundingRectangle.move(m_Velocity.x, m_Velocity.y);
	return false;
}


// Set the direction ( state )
void DynamicObject::setDirection(int direction)
{
	m_Direction = direction;
}

