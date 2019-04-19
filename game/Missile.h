#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
private:
	Sprite missile;
public:
	//====================================================
	// Constructor for missile, sets texture
	//====================================================
	Missile(Texture &missileTexture)
	{
		missile.setTexture(missileTexture);
	}

	//====================================================
	// Sets the position of the missile
	//====================================================
	void setPosition(Vector2f position)
	{
		missile.setPosition(position);
	}

	//====================================================
	// Returns the position of the missile
	//====================================================
	Vector2f getPosition() const
	{
		return missile.getPosition();
	}

	//====================================================
	// Draws the missile
	//====================================================
	void drawMissile(RenderWindow &window)
	{
		window.draw(missile);
	}

	//====================================================
	// Moves the missile upwards by 10
	//====================================================
	void move()
	{
		missile.move(0, -10);
	}

	//===================================================================
	// Checks if missile has hit an enemy, returns a bool if true or not
	//===================================================================
	bool isHit(FloatRect enemyBounds)
	{
		FloatRect missileBounds = missile.getGlobalBounds();
		bool hit;

		if (missileBounds.intersects(enemyBounds))
		{
			hit = true;
		}
		else
			hit = false;
		return hit;
	}
};