#include "Game.h"

using namespace std;

Game::Game(){
	cout << "Game::Game()\n";
	//cout << player.getRect().x << endl;
	isRunning = false;
	gameTitle = nullptr;	
	cout << "	Game created\n";
}

void Game::start() {
	cout << "Game::Start\n";
	cout << gamePlayer->getTextureFile() << endl;
	cout << gameObjects.size() << endl;

}

void Game::quit(){
	cout << "Game::quit()\n";
	isRunning = false;
	//gamePlayer->destroyObject();
	delete gameWindow;
	gameWindow = nullptr;
	gameTitle = nullptr;

	gameObjects.clear();
}

void Game::loadGameObjects()
{
	for (GameObject *obj : gameObjects)
	{		
		gameWindow->loadObject(obj);
	}	
}


Game::~Game() {
	this->quit();
}