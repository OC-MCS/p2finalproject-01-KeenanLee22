#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private: 
	Sprite bomb;
public:
	//====================================================
	// Constructor for Bomb, sets texture and size
	//====================================================
	Bomb(Texture &texture)
	{
		bomb.setTexture(texture);
		bomb.setScale(.1, .1);
	}

	//====================================================
	// Sets the position of a bomb
	//====================================================
	void setPosition(Vector2f position)
	{
		bomb.setPosition(position);
	}

	//====================================================
	// Returns the position of a bomb
	//====================================================
	Vector2f getPosition() const
	{
		Vector2f position = bomb.getPosition();
		return position;
	}

	//====================================================
	// Draws a bomb
	//====================================================
	void drawBomb(RenderWindow &window)
	{
		window.draw(bomb);
	}

	//====================================================
	// Moves a bomb the given distance
	//====================================================
	void moveBomb(float distance)
	{
		
		bomb.move(0, distance);
	}

	//====================================================
	// Checks if a bomb has hit a ship, returns true if hit
	//====================================================
	bool isBombHit(FloatRect shipBounds)
	{
		FloatRect bombBounds = bomb.getGlobalBounds();
		bool hit = false;

		if (bombBounds.intersects(shipBounds))
		{
			hit = true;
		}
		else
			hit = false;
		return hit;
	}
};