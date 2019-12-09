#pragma once
#include "SFML\Graphics.hpp"
class PlayButton
{
private:
	sf::RectangleShape m_Button;
	bool m_displaying = false;
public:
	PlayButton();
	~PlayButton();
};

