#pragma once
#include "Game.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>


class Snake: public Game{

private:
	Game* gameInstance;
	vector<GameObject*> snakeBody;
	GameObject* snakeHead;
	GameObject* snakeTail;
	GameObject* apple;
	GameObject* map;
	Direction lastDirection;
	SDL_Rect appleRect;
	SDL_Rect snakeRect;
	SDL_Rect mapRect;
	int appleFrame;
	int tailSize;
	int screenWidth = 500;
	int screenHeight = 500;
	int snakeBodyDimensions = 25; //25 by 25
	void addTail();
	void moveHead();
	void moveBody();
	void respawnApple();
	void animateApple();
	bool backwardsCheck();
	bool appleCollision();
	bool borderCollision();
	bool gameOver();

public:
	Snake();
	virtual void start();
	virtual bool gameEvents();
	virtual void quit();
	~Snake();

};

