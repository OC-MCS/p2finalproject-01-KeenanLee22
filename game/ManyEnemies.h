#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Enemy.h"
#include <list>


class ManyEnemies
{
private:
	
	list<Enemy> manyEnemies;
	Texture enemyTexture;
	Texture newEnemyTexture;
public:
	//==============================================================================================================
	// Constructor for ManyEnemies, loads both enemy textures and adds 10 enemies in a line at the top of the screen
	//==============================================================================================================
	ManyEnemies()
	{
		if (!enemyTexture.loadFromFile("enemy.png"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!newEnemyTexture.loadFromFile("badder.png"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
		
		addEnemy(Vector2f(50, 40), 0);
	}

	//====================================================
	// Adds 10 enemies in a line at the set position
	//====================================================
	void addEnemy(Vector2f position, int level)
	{
		Vector2f pos = position;
		for (int count = 0; count < 10; count++)
		{
			Enemy temp(enemyTexture);
			temp.setPosition(pos);
			pos.x += 75;
			manyEnemies.push_back(temp);
		}
	}

	//====================================================
	// Draws all enemies in the list
	//====================================================
	void drawEnemies(RenderWindow &window)
	{
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end(); iter++)
		{
			iter->drawEnemy(window);
		}
	}

	//====================================================
	// Finds a random enemy and returns the position of it
	//====================================================
	Vector2f returnRandomEnemy()
	{
		list<Enemy>::iterator iter;
		iter = manyEnemies.begin();
		int random = rand() % manyEnemies.size();
		advance(iter, random);
		return iter->returnEnemySprite().getPosition();
	}

	//====================================================
	// Moves all enemies in the list
	//====================================================
	void moveEnemies(float distance)
	{
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end();)
		{
			iter->moveEnemy(distance);
			if (iter->getPosition().y > 600)
				iter = manyEnemies.erase(iter);
			else
				iter++;
		}
	}

	//====================================================
	// Returns the list of enemies
	//====================================================
	list<Enemy> &returnList()
	{
		return manyEnemies;
	}

	//====================================================
	// Resets all enemies in the set position
	//====================================================
	void resetEnemies()
	{
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end();iter++)
		{
			Vector2f pos = iter->getPosition();
			iter->setPosition(Vector2f(pos.x, 40));
		}
	}

	//====================================================
	// Returns the amount of enemies left in the list
	//====================================================
	int getEnemiesLeft()
	{
		int enemiesLeft = 0;
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end(); iter++)
		{
			enemiesLeft++;
		}
		return enemiesLeft;
	}
	
	//====================================================================
	// Checks if enemies have reached the ship, returns true if they have
	//====================================================================
	bool checkY()
	{
		bool shipHit = false;

		Enemy temp = manyEnemies.front();
		if (temp.getPosition().y >= 450)
		{
			shipHit = true;
		}
		
	
		return shipHit;
		
	}

	//====================================================
	// Sets enemies based on level
	//====================================================
	void setEnemies(int num, int level) 
	{
		manyEnemies.clear();
		float enemyx = 50;
		addEnemy(Vector2f(enemyx, 40), level);

	}

	//========================================================================
	// Sets the new enemies, loading new texture (level 2), and adding them in
	//========================================================================
	void setNewEnemies()
	{
		manyEnemies.clear();
		setTexture(newEnemyTexture);
		
		float enemyx = 50;
		addEnemy(Vector2f(enemyx, 40), 1);
		
	}

	//====================================================
	// Sets the texture of the enemies
	//====================================================
	void setTexture(Texture &texture)
	{
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end(); iter++)
		{
			iter->setTexture(newEnemyTexture);
		}
	}

	//===========================================================================================
	// Creates the new level (level2) of the enemies, clearing old enemies and adding in new ones
	//===========================================================================================
	void setNewLevel(int level)
	{
		manyEnemies.clear();
		
		setNewEnemies();
		setTexture(newEnemyTexture);
	}
};