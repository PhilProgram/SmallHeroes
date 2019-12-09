#pragma once

#include "Board.h"
#include"level.hpp"
#include "MainMenu.h"

class GameClient
{
protected:
	int curentLevel = 0;
	
	// Death, Game Over, Winner Winner
	sf::Texture gameTextures[4];
	MainMenu m_Menu;



	Texture spaceBackground;
	
	sf::RenderWindow window;
	
	
	Board m_Board;
	
public:
	Sprite background;
	void deathSequence();
	void playGame(Level &level);
	void initiateObjects(Level &level);
	void constructBoard();
	void initiateLevel(Level &level);
	bool DisplayMainMenu();
	void initiateGame();

	bool displayMainMenu(sf::RenderWindow &window);
	bool playingGame = true;

	void setCurrentLevel(int level);
	int getCurrentLevel();


	GameClient(); 

};


