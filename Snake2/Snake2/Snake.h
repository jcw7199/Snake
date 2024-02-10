#pragma once
#include "Game.h"
#include "SnakeBodyPart.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>


class Snake: public Game{

private:
	
	int appleFrame;
	int tailSize;
	int snakeVelocity = 25;
	int screenWidth = 500;
	int screenHeight = 500;
	int center_x = screenWidth / 2;
	int center_y = screenHeight / 2;
	int snakeBodyDimensions = 25; //25 by 25
	SDL_Surface* mapSurface = SDL_LoadBMP("images/map.bmp");
	
	SDL_Rect mapRect = { 0, 0, mapSurface->w, mapSurface->h };
	SDL_Rect appleRect = { 0,0,snakeBodyDimensions * 2, snakeBodyDimensions * 2 };
	SDL_Rect snakeRect = { center_x, center_y, snakeBodyDimensions,snakeBodyDimensions };
	SDL_Rect windowRect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mapSurface->w, mapSurface->h }; 
	SDL_Rect lastPosition;


	list<SnakeBodyPart*> snakeBody;
	SnakeBodyPart* snakeHead = new SnakeBodyPart(snakeRect, "images/head.bmp", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	GameObject* apple = new GameObject(appleRect, "images/apple/1.bmp", MOVEMENT_TYPE::STATIC, Direction::NONE);;
	GameObject* map = new GameObject(mapRect, "images/map.bmp", MOVEMENT_TYPE::STATIC, Direction::NONE);

	
	
	void addTail();
	void moveHead();
	void moveBody();
	void respawnApple();
	void animateApple();
	bool backwardsCheck();
	bool appleCollision();
	bool borderCollision();
	bool bodyCollision();
	bool gameOver();

public:
	Snake();
	virtual void start();
	virtual bool gameEvents();
	virtual void quit();
	~Snake();

};

