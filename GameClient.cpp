#include "GameClient.h"
#include "Wizard.h"
#include "Tile.h"
#include "Spike.h"
#include "Checkpoint.h"
#include "Troll.h"
#include "MovementBlocker.h"
#include "Elevator.h"
#include "Ladder.h"
#include "Goal.h"
sf::Vector2f first_Position{};

int main()
{
	
	// Gameclient - Initiate things like main menu etc
	
	

	
	GameClient SmallHeroes;
	if (SmallHeroes.DisplayMainMenu())
	{
		SmallHeroes.initiateGame();

		// A wise choice was made to select level, now lets play
		// Start game initiating
		// Get the level
		// Load it.
		// Blah
		// For now, just get the fucking view to work with a 2d board. 
		//std::cout << "Initiating the game now!" << std::endl;
	}
	
	

	return 0;
}

void GameClient::deathSequence()
{
	m_Board.heroDeathAnimation(window);
	
}

/////////////////////////////////////////////////////////
//					Main loop
/////////////////////////////////////////////////////////
void GameClient::playGame(Level &m_CurrentLevel)
{
	window.create(VideoMode::getDesktopMode(), "Small Heroes");
	

	sf::Color clr{ 38,43, 88 };
	background.setScale(0, 0);

	sf::Music music;
	music.setLoop(1);
	if (!music.openFromFile("pewducktheme.ogg"))
	{
		std::cout << "error loading music";

	}
	music.play();
	music.setVolume(30);
		
	    int direction = 4;
	    sf::Vector2f Velocity;
	    
		sf::Clock clock;
		sf::Clock delta;
		sf::Time deltaTime;
		
		window.setFramerateLimit(60);

		while (window.isOpen())
		{
			direction = 4;
			Velocity = { 0,0 };
			deltaTime = delta.getElapsedTime();
			delta.restart().asSeconds();
			//std::cout << 1.0f/deltaTime.asSeconds() << std::endl;
			sf::Vector2f coords4movement{ 0,0 };
			// float time = board.startClock
			float time = (float)(clock.getElapsedTime().asMicroseconds());
			
			clock.restart();

			time = time / 500;

			if (time > 40) time = 40;


			sf::Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == sf::Event::Closed)
				{
					window.close();
					exit(1);
				}
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
				{
					m_Board.updateHero(sf::Vector2f{ 0,0 }, 5, deltaTime);
				}
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::Right:
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
						{
							direction = 1;
							Velocity = { 5,0 };
							
						}
						coords4movement.x = 5;
						
					}
					break;
					case sf::Keyboard::Left:
					{
						
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
						{
							direction = 2;
							Velocity = { -5,0 };
							
						}
						
						coords4movement.x = -5;
					}

					break;
					case sf::Keyboard::Escape:

						exit(1);
						break;
						
					case sf::Keyboard::Space:
						
						direction = 3;
						Velocity = { 0,-180 };
						
						break;

					case sf::Keyboard::LControl:

						direction = 77;
						m_Board.createBullet(5);
						Velocity = { -5,0 };

						//CreateBullet(dyanmicobject[0].getPosition(), dynamicobj[0].getdirection, bulletspeed);

						//Add it to vector
						break;
					}
				}

			}
			
			// Update ALL DYNAMIC CHARACTERS
			m_Board.updateHero(Velocity, direction, deltaTime);
			window.clear(clr);
			//window.draw(background);
			m_Board.moveDynamics();
			m_Board.checkForCollision();
			// Not in use yet
			

			// Death sequence needs some debug
			if (m_Board.heroDead())
			{
				
				//std::system("pause");
				// Death sequence needs some debug
				//deathSequence();
			}
			if (m_Board.levelCompletion())
			{
				music.pause();
				if (displayMainMenu(window))
				{
					m_Board.reset();
					return;
				}
			}

			//window.draw(background);
			m_Board.checkDynamics();
			m_Board.updateView(window, coords4movement);
			m_CurrentLevel.Draw(window);
			m_Board.m_Update(time, window);
			window.display();
			
		
	}
}
/////////////////////////////////////////////////////////
//					Object factory
/////////////////////////////////////////////////////////
void GameClient::initiateObjects(Level &level)
{

	sf::Vector2f firstCoords;
	bool firstCheck = false;

	std::string m_objectName;
	std::vector<Object> m_LevelObjects;
	m_LevelObjects = level.GetAllObjects();

	vector < unique_ptr<StaticObject>> m_Checkpoints;
	vector<unique_ptr<DynamicObject>> m_DynamicObject1;
	vector < unique_ptr<StaticObject>> m_StaticObject1;
	// Construct bricks
	for (auto i : m_LevelObjects)
	{
		// Get Name
		m_objectName = i.name;
		
		if (m_objectName == "Wall")
		{
			std::cout << "Creating Wall";
			std::cout << i.sprite.getPosition().x << " " << i.sprite.getPosition().y << std::endl;
			// Insert Brick
			m_StaticObject1.push_back(std::make_unique<Tile>(i.sprite, i.rect, i.rect.width,i.rect.height));
		}
		if (m_objectName == "MrCircle")
		{
			m_DynamicObject1.push_back(std::make_unique<Wizard>(i.sprite,i.rect,i.rect.width,i.rect.height));	
			std::reverse(m_DynamicObject1.begin(), m_DynamicObject1.end());
		}
		if (m_objectName == "Thorns")
		{
			m_StaticObject1.push_back(std::make_unique<Spike>(i.sprite, i.rect, i.rect.width, i.rect.height));
		}
		if (m_objectName == "Checkpoint")
		{
			if (!firstCheck)
			{
				firstCoords = i.sprite.getPosition();
				firstCheck = true;

			}
			m_StaticObject1.push_back(std::make_unique<Checkpoint>(i.sprite, i.rect, i.rect.width, i.rect.height));
		}
		if (m_objectName == "Troll")
		{
			m_DynamicObject1.push_back(std::make_unique<Troll>(i.sprite, i.rect, i.rect.width, i.rect.height));
			std::cout << "creating trol";
		}
		if (m_objectName == "MovementBlocker")
		{
			m_StaticObject1.push_back(std::make_unique<MovementBlocker>(i.sprite, i.rect, i.rect.width, i.rect.height));
		}
		if (m_objectName == "Elevator")
		{
			m_DynamicObject1.push_back(std::make_unique<Elevator>(i.sprite, i.rect, i.rect.width, i.rect.height));
		}
		if (m_objectName == "Goal")
		{
			m_StaticObject1.push_back(std::make_unique<Goal>(i.sprite, i.rect, i.rect.width, i.rect.height));
		}

	}
	
	m_DynamicObject1[0]->setResetPosition(firstCoords);
	// Construct the board;
	m_Board.initiateBoard(m_DynamicObject1,m_StaticObject1);
	
}



void GameClient::constructBoard()
{
}

void GameClient::initiateLevel(Level &level)
{
	if (m_Menu.getLevelSelection() == 1)
	{
		if (!level.LoadFromFile("lelelOne.tmx"))  std::cerr << "cannot open file level";
		spaceBackground.loadFromFile("darkcity.jpg");
		background.setTexture(spaceBackground);
	}

	if (m_Menu.getLevelSelection() == 2)
	{
		if (!level.LoadFromFile("level1.tmx"))  std::cerr << "cannot open file level";
		spaceBackground.loadFromFile("darkcity.jpg");
		background.setTexture(spaceBackground);
	}
	
	if (m_Menu.getLevelSelection() == 3)
	{
		if (!level.LoadFromFile("level2.tmx"))  std::cerr << "cannot open file level";
		spaceBackground.loadFromFile("darkcity.jpg");
		background.setTexture(spaceBackground);
	}
	
	
}

bool GameClient::DisplayMainMenu()
{
	return displayMainMenu(window);

}

void GameClient::initiateGame()
{
	// 1) Initiate Level
	// 2) Create Dynamic Objects and Static Objects
	// 3) Pass both arrays to board in constructor
	// 4) Start the game. 
	/////////////////////////////////////////////////////////////////
	// Initiate Level and Objects from Tiled Program  (xml extention)
	/////////////////////////////////////////////////////////////////
	
	
	//PlayGame
	while (1)
	{
		Level m_CurrentLevel;
		initiateLevel(m_CurrentLevel);
		initiateObjects(m_CurrentLevel);
		/////////////////////////////////////////////////////////////////
		window.clear();
		playGame(m_CurrentLevel);
	}
	
	
}







bool GameClient::displayMainMenu(sf::RenderWindow &jk)
{

	sf::Vector2i mousePlace{ 0,0 };
	//sf::RenderWindow m_Window;
	jk.setMouseCursorVisible(1);
	//m_Window.setSize(sf::Vector2u{ 800,600 });
    jk.create(sf::VideoMode(800, 600), "Small Heroes");
	jk.clear();
	m_Menu.initialize();
	m_Menu.display(jk);
	jk.display();
	//sf::sleep(sf::seconds(2.5));
	// Three Buttons on main menu  Play
	// Instructions
	// Exit
	// Instructions -> Display a text I guess"
	sf::Vector2f mouseCoordinates;
	sf::Event event;
	while (jk.isOpen())
	{


		//m_window.setSize(800, 600);
		while (jk.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				jk.close();
				break;
			case sf::Event::MouseButtonPressed:
				mousePlace = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
				if (m_Menu.m_Contains(mousePlace))
				{
					return true;
				}
				break;


			case sf::Event::MouseMoved:
				mousePlace = sf::Vector2i{ event.mouseMove.x , event.mouseMove.y };

				break;

			}
		}
		m_Menu.updateOutline(mousePlace);
		jk.clear();
		m_Menu.display(jk);
		jk.display();
	}
	return false;
}

void GameClient::setCurrentLevel(int level)
{
	//ameClient = level;
}

int GameClient::getCurrentLevel()
{

	return 0;
}

GameClient::GameClient()
{
}
