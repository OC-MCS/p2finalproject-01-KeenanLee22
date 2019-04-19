#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Ship.h"
#include "ManyEnemies.h"
enum Level {LEVEL_1, LEVEL_2};

class BackgroundUI
{
private:
	Sprite background;
	Texture starsTexture;
public:
	//===============================================================
	// Constructor for BackgroundUI, sets background texture and size
	//===============================================================
	BackgroundUI()
	{
		if (!starsTexture.loadFromFile("stars.jpg"))
		{
			cout << "Unable to load stars texture!" << endl;
			exit(EXIT_FAILURE);
		}
		
		background.setTexture(starsTexture);
		background.setScale(1.5, 1.5);
	}

	//====================================================
	// Draws the background
	//====================================================
	void drawBackground(RenderWindow &window)
	{
		window.draw(background);
	}

	//==========================================================
	// Displays the start screen, returns bounds of start button
	//==========================================================
	FloatRect displayMenu(RenderWindow &win)
	{
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("Failure loading font");
		Text Title("Space Invaders", font, 50);
		Text Start("Start Game", font, 35);
		Title.setPosition(220, 200);
		Start.setPosition(310, 300);
		win.draw(Title);
		win.draw(Start);
		FloatRect StartPos = Start.getGlobalBounds();
		return StartPos;
	}

	//=============================================================
	// Displays in the top left corner number of lives the ship has
	//=============================================================
	void displayLives(RenderWindow &win, Ship ship)
	{
		Font font;
		int lives = ship.getLives();
		string livesString = to_string(lives);
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("Failure loading font");
		Text LivesTitle("Lives: ", font, 22);
		Text LivesNumber(livesString, font, 22);
		LivesTitle.setPosition(30, 10);
		LivesNumber.setPosition(100, 10);
		win.draw(LivesTitle);
		win.draw(LivesNumber);
	}

	//=================================================================
	// Displays in top left corner number of enemies left for the level
	//=================================================================
	void displayEnemiesLeft(RenderWindow &win, ManyEnemies manyEnemies)
	{
		Font font;
		int enemiesLeft = manyEnemies.getEnemiesLeft();
		string enemiesLeftString = to_string(enemiesLeft);
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("Failure loading font");
		Text enemiesLeftTitle("Enemies Left: ", font, 22);
		Text enemiesLeftNumber(enemiesLeftString, font, 22);
		enemiesLeftTitle.setPosition(30, 40);
		enemiesLeftNumber.setPosition(170, 40);
		win.draw(enemiesLeftTitle);
		win.draw(enemiesLeftNumber);
	}

	//==================================================================
	// Checks if start button has been clicked, returns true if clicked
	//==================================================================
	bool startClicked(Vector2f mouse, FloatRect StartPos)
	{
		bool startClicked = false;
		
		if (StartPos.contains(mouse))
		{
			startClicked = true;
		}
		else
		{
			startClicked = false;
		}
		return startClicked;
	}

	//====================================================
	// Displays error message and exits the program
	//====================================================
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}

	//===========================================================================================
	// Displays aliens win screen if ship is destroyed, displays level 1 complete if player wins
	// Returns bounds for restart or next level, based on if enemies or player wins/which screen is displayed
	//===================================================================================================
	FloatRect displayEndScreen(bool lost, RenderWindow &win)
	{
		FloatRect clickBounds;
		if (lost)
		{
			Font font;
			if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
				die("Failure loading font");
			Text AliensWin("ALIENS WIN", font, 70);
			Text Restart("RESTART", font, 50);
			AliensWin.setPosition(150, 200);
			Restart.setPosition(200, 400);
			win.draw(AliensWin);
			win.draw(Restart);
			clickBounds = Restart.getGlobalBounds();
		}
		else if (!lost)
		{
			Font font;
			if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
				die("Failure loading font");
			Text PlayerWins("LEVEL 1 COMPLETE", font, 70);
			Text NextLevel("NEXT LEVEL", font, 50);
			PlayerWins.setPosition(50, 200);
			NextLevel.setPosition(200, 400);
			win.draw(PlayerWins);
			win.draw(NextLevel);
			clickBounds = NextLevel.getGlobalBounds();
		}
		return clickBounds;
	}

	//==================================================================================
	// Displays player wins screen after level 2 complete, returns bound of quit button
	//==================================================================================
	FloatRect displayFinalScreen(RenderWindow &win)
	{
		FloatRect clickBounds;
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("Failure loading font");
		Text PlayerWins("PLAYER WINS", font, 70);
		Text Restart("QUIT", font, 50);
		PlayerWins.setPosition(150, 200);
		Restart.setPosition(200, 400);
		win.draw(PlayerWins);
		win.draw(Restart);
		clickBounds = Restart.getGlobalBounds();
		return clickBounds;
	}

};