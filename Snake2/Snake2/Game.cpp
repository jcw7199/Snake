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
	gameWindow->deleteWindow();
	gameWindow = nullptr;
	gameTitle = nullptr;

	for (int i = 0; i < gameObjects.size(); i++) {
			//gameObjects[i]->destroyObject();
	}
	gameObjects.empty();
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