#include "GameObject.h"


bool GameObject::intersects(GameObject & otherObject)
{

	if (m_BoundingRectangle.getGlobalBounds().intersects(otherObject.m_BoundingRectangle.getGlobalBounds()))
	{
		return true;
	}
	return false;
}


GameObject::~GameObject()
{
}
