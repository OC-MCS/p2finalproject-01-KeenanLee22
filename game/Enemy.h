#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include "Missile.h"
class Enemy
{
private:
	Sprite enemy;
public:
	//====================================================
	// Constructor for Enemy, sets texture 
	//====================================================
	Enemy(Texture &texture)
	{
		enemy.setTexture(texture);
	}

	//====================================================
	// Sets the position of the Enemy
	//====================================================
	void setPosition(Vector2f position)
	{
		enemy.setPosition(position);
	}

	//====================================================
	// Returns the position of the enemy
	//====================================================
	Vector2f getPosition() const 
	{
		Vector2f position = enemy.getPosition();
		return position;
	}

	//====================================================
	// Draws an enemy
	//====================================================
	void drawEnemy(RenderWindow &window)
	{
		window.draw(enemy);
	}

	//====================================================
	// Returns the enemy sprite
	//====================================================
	Sprite returnEnemySprite()
	{
		return enemy;
	}

	//====================================================
	// Moves an enemy based on distance passed
	//====================================================
	void moveEnemy(float distance)
	{
		enemy.move(0, distance);
	}

	//=====================================================================================
	// Checks if an enemy has been hit by a missile, erases misile and returns true if hit
	//=====================================================================================
	bool IsEnemyHit(list<Missile> &manyMissiles)
	{
		bool enemyHit = false;
		list<Missile>::iterator tempMissile;
		for (tempMissile = manyMissiles.begin(); tempMissile != manyMissiles.end() && !enemyHit;)
		{
			if (tempMissile->isHit(enemy.getGlobalBounds()))
			{
				tempMissile = manyMissiles.erase(tempMissile);
				enemyHit = true;
			}
			else
				tempMissile++;
		}
		return enemyHit;
	}

	//====================================================
	// Sets the size of the enemy 
	//====================================================
	void setScale(int num)
	{
		enemy.setScale(num, num);
	}

	//====================================================
	// Sets the texture of the enemy
	//====================================================
	void setTexture(Texture &texture)
	{
		enemy.setTexture(texture);
	}
};