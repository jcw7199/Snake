#pragma once
#include "GameWindow.h"
#include "GameObject.h"
#include "TextObject.h"
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
	vector<TextObject*> textObjects;

	Game();
	virtual void start() = 0;
	virtual void quit() = 0;
	virtual bool gameEvents() = 0;
	void loadObjects();
	~Game();
};

