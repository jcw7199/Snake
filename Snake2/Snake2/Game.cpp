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
void Game::loadObjects()
{
	cout << "Game::loadObjects()\n";

	for (GameObject *obj : gameObjects)
	{		
		gameWindow->loadGameObject(obj);
	}	

	for (TextObject* obj : textObjects)
	{
		//SDL_TriggerBreakpoint();
		gameWindow->loadTextObject(obj);
	}
	
}

// Game destructor
Game::~Game() 
{
	cout << "Game::~Game()\n";
	delete gameWindow;
	delete gamePlayer;

	gameObjects.clear();

	gameWindow = nullptr;
	gameTitle = nullptr;
	gamePlayer = nullptr;
}