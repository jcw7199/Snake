#pragma once
#include "GameObject.h"



class SnakeBodyPart : public GameObject
{
public:
	SnakeBodyPart(SDL_Rect bodyPosition, const char* bodyImage, MOVEMENT_TYPE mvmnt, Direction current);
	Direction lastDirection;
	Direction currentDirection;
	Direction nextDirection;
	void printDirection();


};

