#include "Game.h"

using namespace std;

Game::Game(const char* title, GameObject *player, GameObject* background, SDL_Rect windowDimensions){
	cout << "Game::Game()\n";
	//cout << player.getRect().x << endl;
	isRunning = true;
	gameTitle = title;
	gameWindow = new GameWindow(gameTitle, windowDimensions);
	gameBackground = background;
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