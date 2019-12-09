#pragma once

//#include <vector>
#include "PlayButton.h"
#include <SFML/Audio.hpp>
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void buttonClick() { clickSound.play(); }
	void display(sf::RenderWindow &window);
	void initialize();
	void updateOutline(sf::Vector2i &mousecoord);
	void displayLevels();
	void createMenuInterface();
	bool m_Contains(sf::Vector2i &mousecoord);
	int getLevelSelection() { return levelSelected; };
private:
	//			      1)  Play Game
	//				  2)  Level Selection
	//				  3)  Exit
	//			      4)  Save game
	//				  5)  Load Game
	// Controller will access this member to know what was selected
	int levelSelected = -1;
	std::vector<sf::RectangleShape> m_buttons;
	std::vector<sf::RectangleShape> m_levelButtons;
	sf::Texture texture[4];
	sf::Texture leveltexture[4];
	int menuInterface = 0;
	sf::SoundBuffer bufferClick;
	sf::Sound clickSound;
};

