#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "Missile.h"
using namespace sf;


class ManyMissiles
{
private:
	list<Missile> manyMissiles;
	Texture missileTexture;
public:
	//====================================================
	// Constructor for ManyMissiles, load missile texture
	//====================================================
	ManyMissiles()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	//================================================================
	// Adds a missile to the linked list and sets the position of each
	//================================================================
	void addMissile(Vector2f position)
	{
		Missile temp(missileTexture);
		temp.setPosition(position);
		manyMissiles.push_back(temp);
	}

	//====================================================
	// Draws all missiles in the linked list
	//====================================================
	void drawMissiles(RenderWindow &window)
	{
		list<Missile>::iterator iter;
		for (iter = manyMissiles.begin(); iter != manyMissiles.end(); iter++)
		{
			iter->drawMissile(window);
		}
	}

	//====================================================
	// Moves all missiles in the linked list
	//====================================================
	void moveMissiles()
	{
		list<Missile>::iterator iter;
		for (iter = manyMissiles.begin(); iter != manyMissiles.end();)
		{
			iter->move();
			if (iter->getPosition().y < 0)
				iter = manyMissiles.erase(iter);
			else
				iter++;
		}
	}

	//====================================================
	// Deletes a missile from the list if it hits an enemy
	//====================================================
	void deleteMissile(list<Enemy> &manyEnemies)
	{
		bool isHit = false;
		list<Enemy>::iterator iter;
		for (iter = manyEnemies.begin(); iter != manyEnemies.end() && !isHit;)
		{
			if (iter->IsEnemyHit(manyMissiles))
			{
				iter = manyEnemies.erase(iter);
				isHit = true;
			}
			else
				iter++;
		}
	}

	//====================================================
	// Clears all missiles from the list
	//====================================================
	void clearMissiles()
	{
		manyMissiles.clear();
	}
};
