#include "Game.h"

using namespace std;

// default constructor
Game::Game() {
	cout << "Game::Game()\n";
	//cout << player.getRect().x << endl;
	gamePlayer = nullptr;
	gameTitle = nullptr;
	gameWindow = nullptr;
	cout << "	Game created\n";
}

// loads game objects by passing each one to the game window. 
void Game::loadGameObjects()
{
	for (GameObject *obj : gameObjects)
	{		
		gameWindow->loadObject(obj);
	}	
}

// Game destructor
Game::~Game() 
{
	delete gameWindow;
	delete gamePlayer;

	gameObjects.clear();

	gameWindow = nullptr;
	gameTitle = nullptr;
	gamePlayer = nullptr;
}