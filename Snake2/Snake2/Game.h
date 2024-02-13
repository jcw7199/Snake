#pragma once
#include "GameWindow.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <list>

// abstract class for game
class Game
{
public:
	const char* gameTitle;
	GameObject* gamePlayer;
	GameWindow* gameWindow;
	vector<GameObject*> gameObjects;

	Game();
	virtual void start() = 0;
	virtual void quit() = 0;
	virtual bool gameEvents() = 0;
	void loadGameObjects();
	~Game();
};

