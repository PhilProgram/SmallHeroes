#include "Controller.h"
sf::RectangleShape gameOverPic(sf::Vector2f(800, 600));
//#include <iostream>
#include <SFML/Audio.hpp>
sf::Sound buttonSound;
sf::Sound levelComplete;
sf::Sound winner;
sf::SoundBuffer winnerBuffer;
sf::SoundBuffer levelCompleteBuffer;
sf::SoundBuffer buttonBuffer;
sf::SoundBuffer deathBuffer;
sf::SoundBuffer gameOverBuffer;

sf::Sound deathSound;
sf::Sound gameOver;



bool soundPlayed = false;

Controller::Controller()
{
}

Controller::~Controller()
{
}





