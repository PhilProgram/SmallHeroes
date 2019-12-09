#pragma once

#include <memory>
#include <functional>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Camera.h"
#include <exception>
#include "Bullet.h"
//float m_Gravity = 0.1;
using std::vector;
using std::unique_ptr;
class Board
{
private:

	int numOfCheckpoints = 0;
	int checkPoints = -1;
	sf::Texture gameBackground[1];
	//Level m_CurrentLevel;
	//vector<Object> m_BoardObjects;
	
	vector<unique_ptr<DynamicObject>> m_deadCharacters;
	vector<unique_ptr<DynamicObject>> m_DynamicObject;
	vector < unique_ptr<StaticObject>> m_StaticObject;
	vector < unique_ptr<StaticObject>> m_Checkpoints;
	Camera my_Camera;
	//sf::Texture m_GameTextures[4];
	sf::Sprite spaceBackground;

	
public:
	//CreateBullet(dyanmicobject[0].getPosition(), dynamicobj[0].getdirection, bulletspeed);
	
	void createBullet(double speed);
	void reset();
	bool levelCompletion();
	void moveDynamics();
	bool heroDead();
	void updateHero(sf::Vector2f direction, int directions, sf::Time deltatime);
	void checkForCollision();
	bool flipped = false;
	void checkDynamics();
	void updateView(sf::RenderWindow &window, sf::Vector2f &velocity);
	void m_Update(float &time, sf::RenderWindow &window);
	void initiateBoard(vector<std::unique_ptr<DynamicObject>> &Dynamicobjects, vector<std::unique_ptr<StaticObject>> &Staticobjects);
	
	void heroDeathAnimation(sf::RenderWindow &window);

	Board();
	~Board();
};

