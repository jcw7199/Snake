#pragma once
#include "GameWindow.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class Game
{
public:

	const char* gameTitle;
	GameObject* gamePlayer;
	GameObject* gameBackground;
	GameWindow* gameWindow;
	vector<GameObject*> gameObjects;

	Game(const char* title, GameObject* player, GameObject* background, SDL_Rect rect = { 640, 640, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED });
	virtual void start();
	virtual void quit();
	virtual bool gameEvents() = 0;
	bool isRunning;
	~Game();
};

