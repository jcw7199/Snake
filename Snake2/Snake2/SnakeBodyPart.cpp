#include "SnakeBodyPart.h"

SnakeBodyPart::SnakeBodyPart(SDL_Rect bodyPosition, const char* bodyImage, MOVEMENT_TYPE mvmnt, Direction current) : GameObject(bodyPosition, bodyImage, mvmnt)
{
	cout << "SnakeBodyPart::SnakeBodyPart()\n";

	currentDirection = current;
	lastDirection = Direction::NONE;
	nextDirection = Direction::NONE;
}

void SnakeBodyPart::printDirection()
{
	cout << "SnakeBodyPart::printDirection()\n";

	switch (currentDirection)
	{
	case Direction::UP:
		cout << "current direction = UP" << endl;
		break;

	case Direction::DOWN:
		cout << "current direction = DOWN" << endl;
		break;

	case Direction::LEFT:
		cout << "current direction = LEFT" << endl;
		break;

	case Direction::RIGHT:
		cout << "current direction = RIGHT" << endl;
		break;
	
	case Direction::NONE:
		cout << "current direction = NONE" << endl;
		break;

	default:
		cout << "no current direction" << endl;
		break;
		break;
	}
}

SnakeBodyPart::~SnakeBodyPart()
{	
	cout << "SnakeBodyPart::~SnakeBodyPart()\n";

	currentDirection = Direction::NONE;
	lastDirection = Direction::NONE;
	nextDirection = Direction::NONE;
}