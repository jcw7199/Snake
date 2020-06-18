#pragma once
#include "Game.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>
class Snake{

private:
	Game* gameInstance;
	vector<SDL_Rect> s_body;
	GameObject* background;
	GameObject* s_head;
	GameObject* s_tail;
	GameObject* apple;
	SDL_Rect app_r;
	SDL_Rect s_r;
	int appleFrame;
	int tailSize;
	int screenWidth = 500;
	int screenHeight = 500;
	int s_dimensions = 25; //25 by 25
	void addTail();
	void moveSnake();
	void respawnApple();
	void animateApple();

public:
	Snake();
	void start();
	bool gameEvents();
	void quit();
	~Snake();

};

