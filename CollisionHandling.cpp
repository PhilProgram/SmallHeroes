#include "CollisionHandling.h"
#include <typeinfo>
#include <typeindex>
#include "Wizard.h"
#include "Tile.h"
#include "SFML\Graphics.hpp"
#include "Spike.h"
#include "Troll.h"
#include "Checkpoint.h" 
#include "MovementBlocker.h"
#include"Elevator.h"
#include "Ladder.h"
#include "Goal.h"

bool debug = true;




sf::Vector2f zeroVector{ 0.0,0.0 };
sf::Time t1 = sf::seconds(0.4f);
namespace { // unnamed namespace — the standard way to make function "static"
	
	///////////////////////////
	// Wizard spike collision//
	///////////////////////////
	void wizardSpike(GameObject& wizard, GameObject& spike)
	{
		
		Wizard& wiz = dynamic_cast<Wizard&>(wizard);
		Spike& thorn = dynamic_cast<Spike&>(spike);

		//wiz.setAnim("climb");
		wiz.dead(true);
 		wiz.m_OuchSound();
		//sleep(sf::seconds(3.0f));
		wiz.m_BoundingRectangle.setPosition(wiz.getCheckPosition());
		

		// Debug
		if (debug) {
			std::cout << "Intersection between WIZARD and SPIKE" << std::endl;
		}

	}
	///////////////////////////
	//    Wizard Checkpoint  //
	///////////////////////////
	void wizardCheckpoint(GameObject& wizard, GameObject& checkpoint)
	{
		Wizard& wiz = dynamic_cast<Wizard&>(wizard);
		Checkpoint& checkp = dynamic_cast<Checkpoint&>(checkpoint);
		if (!checkp.checkPointActive())
		{
			wiz.m_checkpointSound();
		}
		checkp.setCheckpoint(true);
		// If our current is greater, set to new coords
		if (wiz.getCheckPosition().x < checkpoint.m_BoundingRectangle.getPosition().x)
		{
			wiz.setCheckPosition(checkpoint.m_BoundingRectangle.getPosition());
			
		}
		wiz.setAnimation("check");
		// If all checkpoints are true, we have completed the level...



		//std::cout << "Intersection between WIZARD and SPIKE" << std::endl;

	}
	void trollTroll(GameObject& troll, GameObject& t)
	{

	}
	///////////////////////////
	// Wizard tile collision//
	///////////////////////////
	void wizardTile(GameObject& wizard, GameObject& tile)
	{
		// To get the actual types and use them:
		Wizard& wiz = dynamic_cast<Wizard&>(wizard);
		Tile& wall = dynamic_cast<Tile&>(tile);

		// Get intersecting rectangle and base collision on it. ( Instersecting rectangle based on the collision of the two rectangles. 
		sf::FloatRect rectOne;
		wall.m_BoundingRectangle.getGlobalBounds().intersects(wiz.m_BoundingRectangle.getGlobalBounds(), rectOne);
		
		
		
		
		if (!wiz.isOnGround())
		{
			// From Above
			if (wiz.m_BoundingRectangle.getPosition().y < wall.m_BoundingRectangle.getGlobalBounds().top)//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{
				if(rectOne.width > rectOne.height){
					while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
					{
						
						wiz.m_BoundingRectangle.move(0.0f, -0.01f);
						
					}
					wiz.jumpCounter = 0;
					wiz.onGround(true);

					wiz.setAccelerationY(0);
				
				}	
			}
			else if (wiz.m_BoundingRectangle.getPosition().y > wall.m_BoundingRectangle.getPosition().y)//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{
				if (rectOne.width > rectOne.height) {
					while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
					{

						wiz.m_BoundingRectangle.move(0.0f, 0.02f);

					}
				}
			}	
		}
		
			if (rectOne.width < rectOne.height)
			{

				if (wiz.m_BoundingRectangle.getPosition().x < wall.m_BoundingRectangle.getPosition().x)
				{
					while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
					{

						wiz.m_BoundingRectangle.move(-0.01f, 0.0f);

					}
				}
				else if (wiz.m_BoundingRectangle.getPosition().x > wall.m_BoundingRectangle.getPosition().x)
				{
					while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
					{

						wiz.m_BoundingRectangle.move(0.01f, 0.0f);

					}
				}

			}
	}

	//...

	// secondary collision-processing functions that just
	// implement symmetry: swap the parameters and call a
	// primary function
	void tileWizard(GameObject& tile,
		GameObject& wizard)
	{
		wizardTile(wizard, tile);
	}
	void spikeWizard(GameObject &spike, GameObject &wizard)
	{
		wizardSpike(wizard, spike);
	}
	void checkpointWizard(GameObject &checkPoint, GameObject &wizard)
	{
		wizardCheckpoint(wizard, checkPoint);
	}
	void trollTile(GameObject& troll, GameObject& tile)
	{
		Troll& trol = dynamic_cast<Troll&>(troll);
		Tile& wall = dynamic_cast<Tile&>(tile);
		
		sf::FloatRect rectOne;
		wall.m_BoundingRectangle.getGlobalBounds().intersects(trol.m_BoundingRectangle.getGlobalBounds(), rectOne);

		if (trol.m_BoundingRectangle.getPosition().x < wall.m_BoundingRectangle.getPosition().x)
		{
			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(-0.01f, 0.0f);

			}

			trol.setVelocityX(-trol.getVelocity().x);
			trol.setDirection(0);
		}
		else if (trol.m_BoundingRectangle.getPosition().x > wall.m_BoundingRectangle.getPosition().x)
		{

			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(0.01f, 0.0f);

			}
			trol.setVelocityX(-trol.getVelocity().x);
			trol.setDirection(1);
		}
	}

	void tileTroll(GameObject& tile, GameObject& troll)
	{
		trollTile(troll, tile);

	}

	void elevatorTile(GameObject& elevator, GameObject& tile)
	{
		Elevator& elevat = dynamic_cast<Elevator&>(elevator);
		Tile& wall = dynamic_cast<Tile&>(tile);
		sf::FloatRect rectOne;
		wall.m_BoundingRectangle.getGlobalBounds().intersects(elevat.m_BoundingRectangle.getGlobalBounds(), rectOne);






		if (elevat.m_BoundingRectangle.getPosition().x < wall.m_BoundingRectangle.getPosition().x)
		{
			while (elevat.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
			{

				elevat.m_BoundingRectangle.move(-0.01f, 0.0f);

			}

			elevat.setVelocityX(-elevat.getVelocity().x);
			elevat.setDirection(0);
		}
		else if (elevat.m_BoundingRectangle.getPosition().x > wall.m_BoundingRectangle.getPosition().x)
		{

			while (elevat.m_BoundingRectangle.getGlobalBounds().intersects(wall.m_BoundingRectangle.getGlobalBounds()))
			{

				elevat.m_BoundingRectangle.move(0.01f, 0.0f);

			}
			elevat.setVelocityX(-elevat.getVelocity().x);
			elevat.setDirection(1);
		}



		std::cout << "Intersection between ELEEVATOR and TILE" << std::endl;

	}

	void tileElevator(GameObject& tile, GameObject& elevator)
	{
		elevatorTile(elevator, tile);

	}


	void wizardElevator(GameObject& wizard, GameObject& elevator)
	{
		// To get the actual types and use them:
		Wizard& wiz = dynamic_cast<Wizard&>(wizard);
		Elevator& elevat = dynamic_cast<Elevator&>(elevator);

		// Get intersecting rectangle and base collision on it.
		sf::FloatRect rectOne;
		elevat.m_BoundingRectangle.getGlobalBounds().intersects(wiz.m_BoundingRectangle.getGlobalBounds(), rectOne);





		// From Above
		if (wiz.m_BoundingRectangle.getPosition().y < elevat.m_BoundingRectangle.getGlobalBounds().top)//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
		{
			if (rectOne.width > rectOne.height) {
				while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(elevat.m_BoundingRectangle.getGlobalBounds()))
				{

					wiz.m_BoundingRectangle.move(0.0f, -0.01f);

				}
				wiz.jumpCounter = 0;
				wiz.onGround(true);

				wiz.setAccelerationY(0);

			}
		}
		if (wiz.m_BoundingRectangle.getPosition().y > elevat.m_BoundingRectangle.getPosition().y)
		{
			if (rectOne.width > rectOne.height) {
				while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(elevat.m_BoundingRectangle.getGlobalBounds()))
				{

					wiz.m_BoundingRectangle.move(0.0f, 0.02f);

				}
			}
		}


		if (rectOne.width < rectOne.height)
		{

			if (wiz.m_BoundingRectangle.getPosition().x < elevat.m_BoundingRectangle.getPosition().x)
			{
				while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(elevat.m_BoundingRectangle.getGlobalBounds()))
				{

					wiz.m_BoundingRectangle.move(-0.01f, 0.0f);

				}
			}
			else if (wiz.m_BoundingRectangle.getPosition().x > elevat.m_BoundingRectangle.getPosition().x)
			{
				while (wiz.m_BoundingRectangle.getGlobalBounds().intersects(elevat.m_BoundingRectangle.getGlobalBounds()))
				{

					wiz.m_BoundingRectangle.move(0.01f, 0.0f);

				}
			}


		}
	}
	void ElevatorWizard(GameObject& elevator,
		GameObject& wizard)
	{
		wizardTile(wizard, elevator);
	}



	void trollMovementblocker(GameObject& troll, GameObject& movementblocker)
	{
		Troll& trol = dynamic_cast<Troll&>(troll);
		MovementBlocker& blocker = dynamic_cast<MovementBlocker&>(movementblocker);


		sf::FloatRect rectOne;
		blocker.m_BoundingRectangle.getGlobalBounds().intersects(trol.m_BoundingRectangle.getGlobalBounds(), rectOne);

		if (trol.m_BoundingRectangle.getPosition().x < blocker.m_BoundingRectangle.getPosition().x)
		{
			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(blocker.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(-0.01f, 0.0f);
				

			}
			trol.setVelocityX(trol.getVelocity().x * -1);
			
		}
		
		else if (trol.m_BoundingRectangle.getPosition().x > blocker.m_BoundingRectangle.getPosition().x)
		{

			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(blocker.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(0.01f, 0.0f);

			}
			trol.setVelocityX(trol.getVelocity().x * -1);
			
		}

		

		std::cout << "Intersection between TROLL and MOVE" << std::endl;

	}
	void movementblockerTroll(GameObject& movementblocker, GameObject& troll)
	{
		trollTile(troll, movementblocker);

	}
	//////////////////////////////////////////////////////////////////////
	void trollWizard(GameObject& troll, GameObject& wizard)
	{
		Wizard& wiz = dynamic_cast<Wizard&>(wizard);
		Troll& trol = dynamic_cast<Troll&>(troll);

		

		sf::FloatRect rectOne;
		trol.m_BoundingRectangle.getGlobalBounds().intersects(wiz.m_BoundingRectangle.getGlobalBounds(), rectOne);

		if (rectOne.height < rectOne.width)
		{
			wiz.m_SmashSound();
			trol.die();
			trol.reviveCharacter(true);
			wiz.setAccelerationY(-120);
			
		}
		else
		
		{
			wiz.m_UrgSound();
			// Wizard is dead
			// Set the position to previous checkpoint
			//wiz.dead(true);
			wiz.m_BoundingRectangle.setPosition(wiz.getCheckPosition());
		}

		std::cout << "Intersection between WIZARD and troll" << std::endl;

	}
	void trollSpike(GameObject &troll, GameObject& spike)
	{
		Troll& trol = dynamic_cast<Troll&>(troll);
		Spike& spik = dynamic_cast<Spike&>(spike);
		std::cout << "ggggggggggg";


		sf::FloatRect rectOne;
		spik.m_BoundingRectangle.getGlobalBounds().intersects(trol.m_BoundingRectangle.getGlobalBounds(), rectOne);

		if (trol.m_BoundingRectangle.getPosition().x < spik.m_BoundingRectangle.getPosition().x)
		{
			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(spik.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(-0.01f, 0.0f);

			}

			trol.setVelocityX(-trol.getVelocity().x);
			trol.setDirection(0);
		}
		else if (trol.m_BoundingRectangle.getPosition().x > spik.m_BoundingRectangle.getPosition().x)
		{

			while (trol.m_BoundingRectangle.getGlobalBounds().intersects(spik.m_BoundingRectangle.getGlobalBounds()))
			{

				trol.m_BoundingRectangle.move(0.01f, 0.0f);

			}
			trol.setVelocityX(-trol.getVelocity().x);
			trol.setDirection(1);
		}



		std::cout << "Intersection between TROLL and SPIKE" << std::endl;
	}
	void spikeTroll(GameObject &spike, GameObject& troll)
	{
		trollSpike(troll, spike);
	}

	void wizardMovementblocker(GameObject &wizard, GameObject& spike)
	{

	}
	void movementblockerWizard(GameObject &spike, GameObject& wizard)
	{

	}
	void wizardTroll(GameObject &wizard, GameObject& troll)
	{
		trollWizard(troll, wizard);
	}
	void Trolltroll(GameObject &troll, GameObject& trol)
	{
		trollTroll(troll, trol);
	}
	void checkpointTroll(GameObject &checkpoint, GameObject &troll)
	{
		
	}
	void trollCheckpoint(GameObject &checkpoint, GameObject &troll)
	{
		
	}
	
	void wizardGoal(GameObject &wiz, GameObject &goal)
	{
		Wizard& wizard = dynamic_cast<Wizard&>(wiz);
		wizard.m_GoalReach();
		wizard.goalReach(true);
	}
	void goalWizard(GameObject &goal, GameObject &wiz)
	{
		wizardGoal(wiz, goal);
	}
	void trollgoal (GameObject &wiz, GameObject &goal)
	{
		
	}
	void goaltroll(GameObject &goal, GameObject &wiz)
	{
		
	}
	
	using HitFunctionPtr = void(*)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;

		// ** Wizard / Tile **
		phm[Key(typeid(Wizard), typeid(Tile))] = &wizardTile;
		phm[Key(typeid(Tile), typeid(Wizard))] = &tileWizard;
		// ** Wizard / Spike **
		phm[Key(typeid(Wizard), typeid(Spike))] = &wizardSpike;
		phm[Key(typeid(Spike), typeid(Wizard))] = &spikeWizard;
		// ** Wizard / Checkpoint **
		phm[Key(typeid(Wizard), typeid(Checkpoint))] = &wizardCheckpoint;
		phm[Key(typeid(Checkpoint), typeid(Wizard))] = &checkpointWizard;
		// ** Troll / Tile **
		phm[Key(typeid(Troll), typeid(Tile))] = &trollTile;
		phm[Key(typeid(Tile), typeid(Troll))] = &tileTroll;
		// ** Troll / MovementBlocker **
		phm[Key(typeid(Troll), typeid(MovementBlocker))] = &trollMovementblocker;
		phm[Key(typeid(MovementBlocker), typeid(Troll))] = &movementblockerTroll;
		// ** Troll / Spike **
		phm[Key(typeid(Troll), typeid(Spike))] = &trollSpike;
		phm[Key(typeid(Spike), typeid(Troll))] = &spikeTroll;
		// ** Wizard / MovementBlocker **
		phm[Key(typeid(Wizard), typeid(MovementBlocker))] = &wizardMovementblocker;
		phm[Key(typeid(MovementBlocker), typeid(Wizard))] = &movementblockerWizard;
		// ** Troll / Wizard **
		phm[Key(typeid(Troll), typeid(Wizard))] = &trollWizard;
		phm[Key(typeid(Wizard),typeid(Troll))] = &wizardTroll;

		phm[Key(typeid(Troll), typeid(Troll))] = &trollTroll;
		phm[Key(typeid(Troll), typeid(Troll))] = &Trolltroll;

		phm[Key(typeid(Troll), typeid(Checkpoint))] = &checkpointTroll;
		phm[Key(typeid(Checkpoint), typeid(Troll))] = &trollCheckpoint;

		phm[Key(typeid(Troll), typeid(Goal))] = &trollgoal;
		phm[Key(typeid(Goal), typeid(Troll))] = &goaltroll;

		phm[Key(typeid(Elevator), typeid(Tile))] = &elevatorTile;
		phm[Key(typeid(Tile), typeid(Elevator))] = &tileElevator;

		phm[Key(typeid(Wizard), typeid(Goal))] = &wizardGoal;
		phm[Key(typeid(Goal), typeid(Wizard))] = &goalWizard;

		

		phm[Key(typeid(Elevator), typeid(Wizard))] = &ElevatorWizard;
		phm[Key(typeid(Wizard), typeid(Elevator))] = &wizardElevator;
		//...
		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)                      
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
}

