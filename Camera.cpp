#include "Camera.h"

///////////////////////////////////////////
// Constructor - sets the x and y of view//
///////////////////////////////////////////
Camera::Camera() : view(FloatRect(0, 0, 555, 480)) 
{
	
}


Camera::~Camera()
{
}
void Camera::MoveView(sf::Vector2f & coords)
{
	view.move(coords);
}
/////////////////////////////////////////////////////////
// Set position - currently, wizard.x and view center.y//
/////////////////////////////////////////////////////////
void Camera::setPosition(const sf::Vector2f & coords)
{
	if (coords.x < 555 / 2)
	{
		view.setCenter(555 / 2, view.getCenter().y);
	}
	else if (coords.x > 25600-(550/2))
	{	
		view.setCenter(2285, view.getCenter().y);
	}
	else
		view.setCenter(coords.x, view.getCenter().y);
}


// Getters & Setters
void Camera::SetView(sf::RenderWindow& window)
{
	window.setView(view);
}
const sf::Vector2f& Camera::GetCenter(void) const
{
	return view.getCenter();
}
