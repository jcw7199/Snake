#pragma once
#include "GameWindow.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <list>
class Game
{
public:

	static int numberOfObjects;

	const char* gameTitle;
	GameObject* gamePlayer;
	GameWindow* gameWindow;
	vector<GameObject*> gameObjects;

	Game();
	virtual void start();
	virtual void quit();
	virtual bool gameEvents() = 0;
	void loadGameObjects();
	bool isRunning;
	~Game();
};

