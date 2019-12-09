#pragma once
#include "GameObject.h"
class StaticObject :
	public GameObject
{
protected: 
	bool m_isDangerous = 0;
	bool m_isVisible = 0;
public:
	StaticObject();
	virtual ~StaticObject();
};

