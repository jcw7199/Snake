#include "Game.h"

using namespace std;

Game::Game(const char* title, GameObject *player, SDL_Rect windowDimensions){
	cout << "Game::Game()\n";
	//cout << player.getRect().x << endl;
	isRunning = true;
	gameTitle = title;
	gameWindow = new GameWindow(gameTitle, "images/map.bmp", windowDimensions);
	
	if (player != nullptr) {
		cout << "player " << player->getID() << " " << player->getTextureFile();
		gamePlayer = player;
		cout << gamePlayer->getID() << " " << gamePlayer->getTextureFile();

		gameObjects.push_back(gamePlayer);
		
	}
	else {
		gamePlayer = nullptr;
	}

	cout << "	Game created\n";
}

void Game::start() {
	cout << "Game::Start\n";
	cout << gamePlayer->getTextureFile() << endl;
	cout << gameObjects.size() << endl;
	
	while (isRunning) {
		//cout << "running\n";
		gameWindow->present();
		isRunning = gameEvents();
	
		//cout << "o\n";
		for (int i = 0; i < gameObjects.size(); i++) {
			if(gameObjects[i] != nullptr)
				gameWindow->addToRenderer(gameObjects[i]->getTextureFile(), *gameObjects[i]->getRect());
		}
		
	}
}

void Game::quit(){
	cout << "Game::quit()\n";
	isRunning = false;
	gamePlayer->destroyObject();
	gameWindow->deleteWindow();
	gameWindow = nullptr;
	gameTitle = nullptr;

	for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->destroyObject();
	}
	gameObjects.empty();
}

Game::~Game() {
	this->quit();
}