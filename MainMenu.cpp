#include "MainMenu.h"
#include <iostream>

sf::RectangleShape background(sf::Vector2f(800, 600));
MainMenu::MainMenu()
{
	if (!bufferClick.loadFromFile("Select.wav")) {};
	clickSound.setBuffer(bufferClick);
}


MainMenu::~MainMenu()
{
}

void MainMenu::display(sf::RenderWindow &window)
{
	window.draw(background);
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		window.draw(m_buttons.at(i));
	}
}

void MainMenu::initialize()
{



	// Background Texture
	if (!texture[0].loadFromFile("megacool.jpg"))
	{
		std::cout << "Error loading texture";
	}
	// Exit Button Texture
	if (!texture[1].loadFromFile("ExitButton.png"))
	{
		std::cout << "Error loading texture";
	}
	if (!texture[2].loadFromFile("PlayButton.png"))
	{
		std::cout << "Error loading texture";
	}
	if (!texture[3].loadFromFile("levelselect.jpg"))
	{
		std::cout << "Error loading texture";
	}
	///////Level Selection Button Textures//////////////

	if (!leveltexture[0].loadFromFile("levelOne.jpg"))
	{
		std::cout << "Error loading texture";
	}
	if (!leveltexture[1].loadFromFile("levelTwo.jpg"))
	{
		std::cout << "Error loading texture";
	}
	if (!leveltexture[2].loadFromFile("levelThree.jpg"))
	{
		std::cout << "Error loading texture";
	}
	if (!leveltexture[3].loadFromFile("back-icon.png"))
	{
		std::cout << "Error loading texture";
	}
	/////////////////////////////////////////////////

	background.setTexture(&texture[0]);

	createMenuInterface();

	

}

void MainMenu::updateOutline(sf::Vector2i &mousecoord)
{
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons.at(i).getGlobalBounds().contains(sf::Vector2f(mousecoord)))
		{
			m_buttons.at(i).setOutlineColor(sf::Color::Yellow);
			m_buttons.at(i).setOutlineThickness(5.0f);

		}
		else
		{
			m_buttons.at(i).setOutlineColor(sf::Color::Transparent);
			m_buttons.at(i).setOutlineThickness(5.0f);
		}

	}
}

void MainMenu::displayLevels()
{
	sf::RectangleShape LevelOne(sf::Vector2f(300, 200));
	sf::RectangleShape LevelTwo(sf::Vector2f(300, 200));
	sf::RectangleShape LevelThree(sf::Vector2f(300, 200));
	sf::RectangleShape GoBack(sf::Vector2f(300, 200));

	LevelOne.setTexture(&leveltexture[0]);
	LevelOne.setPosition(50, 250);
	LevelOne.setScale(0.5, 0.5);

	LevelTwo.setTexture(&leveltexture[1]);
	LevelTwo.setPosition(300, 250);
	LevelTwo.setScale(0.5, 0.5);

	LevelThree.setTexture(&leveltexture[2]);
	LevelThree.setPosition(550, 250);
	LevelThree.setScale(0.5, 0.5);

	GoBack.setTexture(&leveltexture[3]);
	GoBack.setPosition(300, 450);
	GoBack.setScale(0.5, 0.5);
	

	m_buttons.clear();

	m_buttons.push_back(LevelOne);
	m_buttons.push_back(LevelTwo);
	m_buttons.push_back(LevelThree);
	m_buttons.push_back(GoBack);
	// Main menu = 0, Level selection = 1;
	menuInterface = 1;
}

void MainMenu::createMenuInterface()
{
	m_buttons.clear();

	
	sf::RectangleShape Exitbutton(sf::Vector2f(300, 200));
	sf::RectangleShape LevelSelection(sf::Vector2f(300, 200));

	Exitbutton.setTexture(&texture[1]);
	Exitbutton.setPosition(300, 400);
	Exitbutton.setScale(0.5, 0.5);

	

	LevelSelection.setTexture(&texture[3]);
	LevelSelection.setPosition(300, 250);
	LevelSelection.setScale(0.5, 0.5);


	
	m_buttons.push_back(Exitbutton);
	m_buttons.push_back(LevelSelection);

	// Main menu = 0, Level selection = 1;
	menuInterface = 0;
}

bool MainMenu::m_Contains(sf::Vector2i & mousecoord)
{
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons.at(i).getGlobalBounds().contains(sf::Vector2f(mousecoord)))
		{
			// Main Menu
			if (!menuInterface)
			{
				buttonClick();
				// Exit
				if (i == 0)
				{
					exit(1);
				}
				// Level Selection
				if (i == 1)
				{
					displayLevels();
				}
			}
			// Level Interface
			else
			{
				buttonClick();
				if (i == 0)
				{
					levelSelected = 1;
					return true;
				}
				if (i == 1)
				{
					levelSelected = 2;
					return true;
				}
				if (i == 2)
				{
					levelSelected = 3;
					return true;
				}
				// Go back to menu
				if (i == 3)
				{
					createMenuInterface();
				}
			}
		}
	}
	return false;

}