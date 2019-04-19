#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Bomb.h"

class Ship
{
private:
	Sprite ship;
	Texture shipTexture;
	int lives;
public:

	//==============================================
	// Constructor for ship, sets texture and lives
	//==============================================
	Ship()
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
		ship.setTexture(shipTexture);
		lives = 3;
	}

	//====================================================
	// Sets the position of the ship
	//====================================================
	void setPosition(float x, float y)
	{
		ship.setPosition(x, y);
	}

	//====================================================
	// Returns the position of the ship
	//====================================================
	Vector2f getPosition() const
	{
		return ship.getPosition();
	}

	//====================================================
	// Moves the ship by 5
	//====================================================
	void moveShip()
	{
		const float DISTANCE = 5.0;

		if (Keyboard::isKeyPressed(Keyboard::Left) && (ship.getPosition().x > 0))
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			ship.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && (ship.getPosition().x< (800-shipTexture.getSize().x)))
		{
			// right arrow is pressed: move our ship right 5 pixels
			ship.move(DISTANCE, 0);
		}
	}

	//====================================================
	// Draws the ship
	//====================================================
	void drawShip(RenderWindow &window)
	{
		window.draw(ship);
	}

	//====================================================
	// Decreases the life of the ship by 1
	//====================================================
	void decrementLives()
	{
		lives--;
	}

	//====================================================
	// Sets the lives of the ship
	//====================================================
	void setLives(int l)
	{
		lives = l;
	}

	//====================================================
	// Returns the lives of the ship
	//====================================================
	int getLives()
	{
		return lives;
	}

	//====================================================
	// Returns the ship bounds
	//====================================================
	FloatRect getShipBounds()
	{
		return ship.getGlobalBounds();
	}
};