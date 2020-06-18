#pragma once
#include "GameWindow.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class Game
{
public:	
	GameObject* g_player;
	const char* g_title;
	

	Game(const char* title = "", GameObject *player = nullptr);
	virtual void start();
	virtual void quit();
	GameWindow* g_window;
	void moveObject(GameObject& obj);
	bool collisionDetection(GameObject& obj1, GameObject& obj2);
	virtual bool gameEvents();
	vector<GameObject*> objs;
	bool isRunning;
	~Game();
};

