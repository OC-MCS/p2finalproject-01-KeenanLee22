#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "Bomb.h"
#include <ctime>
#include <cstdlib>
#include "ManyEnemies.h"
using namespace sf;


class ManyBombs
{
private:
	list<Bomb> manyBombs;
	Texture bombTexture;
public:
	//====================================================
	// Constructor for ManyBombs, loads bomb texture
	//====================================================
	ManyBombs()
	{
		if (!bombTexture.loadFromFile("bomb.png"))
		{
			cout << "Unable to load bomb texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	//====================================================
	// Draws all bombs in the list
	//====================================================
	void drawBombs(RenderWindow &window)
	{
		list<Bomb>::iterator iter;
		for (iter = manyBombs.begin(); iter != manyBombs.end(); iter++)
		{
			iter->drawBomb(window);
		}
	}

	//====================================================
	// Adds a bomb to the list
	//====================================================
	void addBomb(Vector2f position)
	{
		Bomb temp(bombTexture);
		temp.setPosition(position);
		manyBombs.push_back(temp);
	}

	//====================================================
	// Moves all bombs in the list
	//====================================================
	void moveBombs(float distance)
	{
		list<Bomb>::iterator iter;
		for (iter = manyBombs.begin(); iter != manyBombs.end();)
		{
			iter->moveBomb(distance);
			if (iter->getPosition().y > 600)
				iter = manyBombs.erase(iter);
			else
				iter++;
		}
	}

	//=================================================================================================================================
	// Deletes a bomb from the list if it has hit a ship, decrements the lives of the ship, and resets enemies to the top of the screen
	//==================================================================================================================================
	void deleteBomb(Ship &ship, ManyEnemies &manyEnemies)
	{
		bool isHit = false;
		list<Bomb>::iterator iter;
		for (iter = manyBombs.begin(); iter != manyBombs.end();)
		{
			if (iter->isBombHit(ship.getShipBounds()) && !isHit)
			{
				ship.decrementLives();
				isHit = true;
				iter = manyBombs.erase(iter);
				manyEnemies.resetEnemies();

			}
			else
			{
				iter++;
			}
		}
	}

	//====================================================
	// Clears all bombs from the list/screen
	//====================================================
	void clearBombs()
	{
		manyBombs.clear();
	}
};