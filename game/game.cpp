#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
using namespace sf;
#include "BackgroundUI.h"
#include "Enemy.h"
#include "Missile.h"
#include "Ship.h"
#include "Bomb.h"
#include "ManyBombs.h"
#include "ManyMissiles.h"
#include "ManyEnemies.h"

//============================================================
// Keenan Lee
// Final Programming Assignment: Game
// 4/19/19
//============================================================

int main()
{
	Ship ship;
	ManyMissiles manyMissiles;
	BackgroundUI backgroundUI;
	ManyBombs manyBombs;
	ManyEnemies manyEnemies;
	int randomSecond;
	bool start = true;
	bool lost = false;
	bool inGame = false;
	float bombSpeed = 5.0;
	float enemyMoveSpeed = 0.9;
	FloatRect StartPos;
	FloatRect clickBounds;
	Vector2f mousePos;
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int MIN_SECONDS = 60;
	const int MAX_SECONDS = 180;
	Level level = LEVEL_1;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	unsigned seed = time(0);
	srand(seed);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	

	// initial position of the ship will be approx middle of screen
	float shipX = window.getSize().x / 2.0f;
	float shipY = 1000 / 2.0f;
	ship.setPosition(shipX, shipY);
	randomSecond = (rand() % (MAX_SECONDS - MIN_SECONDS + 1) + MIN_SECONDS);

	while (window.isOpen())
	{
		Event event;
		backgroundUI.drawBackground(window);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed && !start)
			{
				if (event.key.code == Keyboard::Space)
				{
					Vector2f pos = ship.getPosition();
					manyMissiles.addMissile(Vector2f(pos.x+10,pos.y-10));
				}
				
				
			}
			else if (event.type == Event::MouseButtonPressed &&  Mouse::isButtonPressed(Mouse::Button::Left) && start) 
			{
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (backgroundUI.startClicked(mousePos, StartPos)) // Clicked start button
				{
					start = false;
					inGame = true;
				}
			}
			
		}
		
		
		
		
		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================
		
		if (ship.getLives() == 0) // Ship destroyed, aliens win
		{
			lost = true;
			clickBounds = backgroundUI.displayEndScreen(lost,window);
			inGame = false;
			if (event.type == Event::MouseButtonPressed &&  Mouse::isButtonPressed(Mouse::Button::Left))
			{
				mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (backgroundUI.startClicked(mousePos, clickBounds)) // Restart clicked
				{
					lost = false;
					inGame = true;
					ship.setPosition(shipX,shipY);
					ship.setLives(3);
					level = LEVEL_1;
					bombSpeed = 5.0;
					enemyMoveSpeed = 0.9;
					manyEnemies.setEnemies(10, level);
					manyMissiles.clearMissiles();
					manyBombs.clearBombs();
					randomSecond = (rand() % (MAX_SECONDS - MIN_SECONDS + 1) + MIN_SECONDS);
				}
			}
		}
		else if (manyEnemies.getEnemiesLeft() == 0) //All enemies destroyed
		{
			if (level == LEVEL_1)
			{
				clickBounds = backgroundUI.displayEndScreen(lost, window);
				inGame = false;
				if (event.type == Event::MouseButtonPressed &&  Mouse::isButtonPressed(Mouse::Button::Left))
				{
					mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					if (backgroundUI.startClicked(mousePos, clickBounds))
					{
						inGame = true;
						ship.setPosition(shipX, shipY);
						ship.setLives(3);
						level = LEVEL_2;
						bombSpeed = 10.0;
						enemyMoveSpeed = 1.9;
						manyEnemies.setNewLevel(level);
						manyMissiles.clearMissiles();
						manyBombs.clearBombs();
					}
				}
			}
			else if (level == LEVEL_2)
			{
				inGame = false;
				clickBounds = backgroundUI.displayFinalScreen(window);
				if (event.type == Event::MouseButtonPressed &&  Mouse::isButtonPressed(Mouse::Button::Left))
				{
					mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					if (backgroundUI.startClicked(mousePos, clickBounds))
					{
						window.close();
					}
				}
			}
			
			
		}

		if (randomSecond == 0 && inGame)
		{
			Vector2f enemyPosition = manyEnemies.returnRandomEnemy();
			manyBombs.addBomb(Vector2f(enemyPosition.x,enemyPosition.y+30));
			randomSecond = (rand() % (MAX_SECONDS - MIN_SECONDS + 1) + MIN_SECONDS);

		}
		else
		{
			randomSecond--;
		}

		if (inGame)
		{
			
			
			
			if (manyEnemies.checkY()) // Enemies reach ship
			{
				ship.decrementLives();
				manyEnemies.resetEnemies();
			}

			manyMissiles.moveMissiles();
			ship.moveShip();
			manyBombs.moveBombs(bombSpeed);
			manyEnemies.moveEnemies(enemyMoveSpeed);
			manyMissiles.deleteMissile(manyEnemies.returnList());
			manyBombs.deleteBomb(ship, manyEnemies);
			ship.drawShip(window);
			manyEnemies.drawEnemies(window);
			backgroundUI.displayLives(window, ship);
			backgroundUI.displayEnemiesLeft(window, manyEnemies);
			manyBombs.drawBombs(window);
			manyMissiles.drawMissiles(window);

		}
		else if (start)
		{
			StartPos = backgroundUI.displayMenu(window);
		}
		

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

