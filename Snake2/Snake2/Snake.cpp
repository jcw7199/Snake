#include "Snake.h"

using namespace std;

// Snake constructor
Snake::Snake()
{ 
	cout << "Snake::Snake()\n";
	
	// initialize member variables
	gamePlayer = snakeHead;
	gameTitle = "Snake Game";
	snakeHead = new SnakeBodyPart(snakeRect, "images/head.bmp", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	apple = new GameObject(appleRect, "images/apple/1.bmp", MOVEMENT_TYPE::STATIC);;
	map = new GameObject(mapRect, "images/map.bmp", MOVEMENT_TYPE::STATIC);
	retryScreen = new GameObject(mapRect, "images/game_over.bmp");
	gameWindow = new GameWindow(gameTitle, windowRect);
	tailSize = 1;
	appleFrame = 1;
}

// starts game
void Snake::start() {
	cout << "Snake::start\n";
	
	// initialize window
	gameWindow->init();

	// adds snake objects to game objects list for loading.
	gameObjects.push_back(map);
	gameObjects.push_back(apple);
	gameObjects.push_back(snakeHead);
	snakeBody.push_back(snakeHead);
	
	// spawn apple
	respawnApple();

	// load objects
	loadGameObjects();

	//if not quitting
	if (gameEvents() == false)
	{
		// delete current objects and restart game.
		delete snakeHead;
		delete apple;
		delete map;
		delete retryScreen;
		delete gameWindow;
		gameObjects.clear();
		Snake newSnake = Snake();
		newSnake.start();
	}
	else
	{
		// exit the game
		Snake::quit();
	}

}

// Main game events
bool Snake::gameEvents() {
	cout << "Snake::Game events()" << endl;
	SDL_Event e;
	bool quitting = false;


	int fps = 60;

	// desired time between frames
	int desiredDelta = 3000 / fps;

	// main event loop
	while (quitting == false)
	{
		int startTick = SDL_GetTicks();

		loadGameObjects();

		if (SDL_PollEvent(&e) > 0) {

			if (quitting == true)
			{
				break;
			}

			// if key down, attempt to change direction
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					snakeBody.front()->nextDirection = Direction::UP;
					break;

				case SDLK_DOWN:
					snakeBody.front()->nextDirection = Direction::DOWN;
					break;

				case SDLK_LEFT:
					snakeBody.front()->nextDirection = Direction::LEFT;
					break;

				case SDLK_RIGHT:
					snakeBody.front()->nextDirection = Direction::RIGHT;
					break;

				// if q, quit the game.
				case SDLK_q:
					cout << "quitting" << endl;
					quitting = true;
					break;

				default:
					break;
				}

				// prevent backwards movement
				if (backwardsCheck() == true)
				{
					// if backwards, set maintain current direction
					//cout << "backwards movement detected." << endl;
					snakeBody.front()->nextDirection = snakeBody.front()->currentDirection;
				}

			}
			else
			{
				// check for manual closure of game window
				quitting = gameWindow->eventHandler();
			}
		}


		// check for apple collision.
		if (appleCollision() == true)
		{
			cout << "apple collision detected." << endl;
			snakeBody.front()->printRect();
			addTail();
			respawnApple();
		}

		// check for border collision.
		if (borderCollision() == true)
		{
			cout << "border collision detected." << endl;
			snakeBody.front()->printRect();

			quitting = true;
		}

		// check for body collision.
		if (bodyCollision() == true)
		{
			cout << "body collision detected." << endl;
			quitting = true;
		}


		// move body per iteration of loop.
		moveBody();


		int endTick = SDL_GetTicks();

		// current time between frames
		int delta = endTick - startTick;

		// if time between frames is too fast, delay the game.
		if (delta < desiredDelta)
		{
			SDL_Delay(desiredDelta - delta);

		}

		// if game is lost, ask to play again.
		if (quitting == true)
		{
			quitting = gameOver();

			if (quitting == false)
			{
				cout << "restarting game" << endl;
				gameObjects.clear();
				snakeBody.clear();
				return quitting;
			}
			else
			{
				//SDL_TriggerBreakpoint();
				return quitting;
			}
		}

	}
	return quitting;
}

// Detects backwards movement
bool Snake::backwardsCheck() {
	cout << "Snake::backwardscheck()" << endl;

	// check for opposing directions. 
	if (snakeBody.front()->lastDirection == Direction::NONE)
	{
		return false;
	}
	
	if (   
		   (snakeBody.front()->currentDirection == Direction::UP && snakeBody.front()->nextDirection == Direction::DOWN)
		|| (snakeBody.front()->currentDirection == Direction::DOWN && snakeBody.front()->nextDirection == Direction::UP)
		|| (snakeBody.front()->currentDirection == Direction::LEFT && snakeBody.front()->nextDirection == Direction::RIGHT)
		|| (snakeBody.front()->currentDirection == Direction::RIGHT && snakeBody.front()->nextDirection == Direction::LEFT)
		) 
	{
		return true;
	}
	else {
		return false;
	}
}

// moves snake head
void Snake::moveHead()
{
	//cout << "move head" << endl;

	//store current direction
	snakeBody.front()->lastDirection = snakeBody.front()->currentDirection;

	//based on the keypress and backwards detection, move head.
	switch (snakeBody.front()->nextDirection)
	{
	case Direction::UP:
		//cout << "moving up" << endl;
		snakeBody.front()->getRect()->y -= snakeVelocity;
		snakeBody.front()->currentDirection = Direction::UP;
		break;

	case Direction::DOWN:
		//cout << "moving down" << endl;
		snakeBody.front()->getRect()->y += snakeVelocity;
		snakeBody.front()->currentDirection = Direction::DOWN;
		break;

	case Direction::LEFT:
		//cout << "moving left" << endl;
		snakeBody.front()->getRect()->x -= snakeVelocity;
		snakeBody.front()->currentDirection = Direction::LEFT;
		break;

	case Direction::RIGHT:
		//cout << "moving right" << endl;
		snakeBody.front()->getRect()->x += snakeVelocity;
		snakeBody.front()->currentDirection = Direction::RIGHT;
		break;

	case Direction::NONE:
		//cout << "moving none" << endl;
		break;
	default:
		break;
	}
		
}

// moves snake body
void Snake::moveBody()
{
	
	list<SnakeBodyPart*>::reverse_iterator rev_it;
	list<SnakeBodyPart*>::reverse_iterator prevIt;

	SnakeBodyPart* previous;
	SnakeBodyPart* current;

	//sets each body part to the one before it. 
	//This allows the tail to trail after the head before it.	
	for (rev_it = snakeBody.rbegin(); rev_it != snakeBody.rend(); ++rev_it)
	{
		prevIt = next(rev_it, 1);
		current = *rev_it;
		if (prevIt != snakeBody.rend())
		{
			previous = *prevIt;

			current->nextDirection = previous->currentDirection;			
			current->lastDirection = current->currentDirection;
			current->currentDirection = previous->lastDirection;
			
			current->setRect(*previous->getRect());

		}
		else
		{
			//after moving the body and having it catch up to the head, 
			//move the head.
			moveHead();
		}

	}
	

	//print current body.
	/*
	int i = 0;
	cout << "printing current body\n\n\n" << endl;
	for (SnakeBodyPart* part : snakeBody)
	{
		cout << i << ": ";
		part->printDirection();
		part->printRect();
		i++;
	}
	cout << "finished current body\n\n\n" << endl;
	*/
}

// spawns an apple within the bounds of the game.
void Snake::respawnApple() {
	int x = 0, y = 0;
	
	while (x == 0 || y == 0)
	{
		x = rand() % (screenWidth - snakeBodyDimensions * 2);
		y = rand() % (screenHeight - snakeBodyDimensions * 2);
	}
	
	

	apple->getRect()->x = x;
	apple->getRect()->y = y;
}

// Adds a tail to the snake using the body dimensions as an offset.
void Snake::addTail() {
	cout << tailSize << " Snake::addTail()\n";

	//create a new body part to add to the tail
	SDL_Rect newTailRect = SDL_Rect{ 0, 0, 0, 0 };
	SnakeBodyPart* currentTail = snakeBody.back();
	Direction newTailDirection = Direction::NONE;
	

	//set tailRect to be equal to where the current tail is.
	SDL_Rect tailRect = *currentTail->getRect();

	//based on the current direction, 
	//spawn the new tail behind the current one.
	switch (currentTail->currentDirection)
	{
	case Direction::UP:
		cout << "direction up, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x,
								tailRect.y + snakeBodyDimensions + 5,
								tailRect.w, tailRect.h };
		break;

	case Direction::DOWN:
		cout << "direction down, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x,
								tailRect.y - snakeBodyDimensions - 5,
								tailRect.w, tailRect.h };
		break;

	case Direction::LEFT:
		cout << "direction left, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x + snakeBodyDimensions + 5,
								tailRect.y,
								tailRect.w, tailRect.h };
		break;

	case Direction::RIGHT:
		cout << "direction right, add tail" << endl;

		newTailRect = SDL_Rect{
								tailRect.x - snakeBodyDimensions - 5,
								tailRect.y,
								tailRect.w, tailRect.h };
		break;

	case Direction::NONE:
		cout << "direction none, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x,
								tailRect.y,
								tailRect.w, tailRect.h };
		break;

	default:
		cout << "spawning default tail" << endl;
		newTailRect = SDL_Rect{ 0, 0, 0, 0 };
		newTailDirection = Direction::NONE;
		break;
	}

	// create tail with new offset.
	SnakeBodyPart* newTail = new SnakeBodyPart(newTailRect, "images/tail.bmp", MOVEMENT_TYPE::CONSTANT, newTailDirection);
	newTail->currentDirection = Direction::NONE;
	newTail->lastDirection = Direction::NONE;
	newTail->nextDirection = currentTail->lastDirection;
	
	
	//print old tail
	//cout << "old tail: ";
	//snakeBody.back()->printRect();
	
	gameObjects.push_back(newTail);
	snakeBody.push_back(newTail);
	tailSize++;

	//print new tail
	//cout << "tail size: " << snakeBody.size() <<" new tail: ";
	//snakeBody.back()->printRect();

}

// Detects collision between snake head and apples.
bool Snake::appleCollision()
{
	SDL_Rect* collision = nullptr;
	if (SDL_HasIntersection(snakeBody.front()->getRect(), apple->getRect()) == SDL_TRUE)
	{
		cout << "apple collision" << endl;
		return true;
		
	}

	return false;
}

// Detects collisions with border.
bool Snake::borderCollision() {

	//left border
	if (snakeBody.front()->getRect()->x <= 0)
	{
		cout << "left border" << endl;
		return true;
	}

	//right border
	if (snakeBody.front()->getRect()->x + snakeBodyDimensions >= screenWidth)
	{
		cout << "right border" << endl;
		return true;
	}

	//top border
	if (snakeBody.front()->getRect()->y <= 0)
	{
		cout << "top border" << endl;
		return true;
	}

	//bottom border
	if (snakeBody.front()->getRect()->y + snakeBodyDimensions >= screenHeight)
	{
		cout << "bottom border" << endl;
		return true;
	}
	return false;
}

// Detects collisons with the head and its own body.
bool Snake::bodyCollision()
{

	list<SnakeBodyPart*>::reverse_iterator rev_it;
	list<SnakeBodyPart*>::reverse_iterator prevIt;

	SnakeBodyPart* previous;
	SnakeBodyPart* current;

	// iterate through body, ignoring the head,
	// and check for collision between the head and a body part.
	for (rev_it = snakeBody.rbegin(); rev_it != snakeBody.rend(); ++rev_it)
	{
		if (next(rev_it, 1) != snakeBody.rend())
		{
			current = *rev_it;
			if (SDL_HasIntersection(snakeBody.front()->getRect(), current->getRect()) == SDL_TRUE)
			{
				return true;
			}
		}
	}
	return false;
}

// Presents a game over screen where the player has the option
// to play again or quit entirely
bool Snake::gameOver() {
	cout << "Snake::GameOver()\n";
	SDL_Event e;
	
	//clear game objects.
	snakeBody.clear();
	gameObjects.clear();
	
	//load retry screen
	gameObjects.push_back(retryScreen);
	loadGameObjects();

	cout << "\n\n----------------------------------------\n\n";
	
	cout << "Game Over! Final score: " << tailSize << endl;
	
	cout << "\n\n----------------------------------------\n\n";
	
	tailSize = 0;
	//game over loop
	while (true) 
	{
		if (SDL_PollEvent(&e) > 0) 
		{

			if (e.type == SDL_KEYDOWN) 
			{
				//if keydown is q, quit. If enter, restart game.
				switch (e.key.keysym.sym)
				{
				case SDLK_q:
					cout << "quitting\n";
					return true;

				case SDLK_RETURN:
					cout << "restarting\n";
					return false;
				}
			}
			else if (e.type == SDL_QUIT)
			{
				cout << "quitting" << endl;
				return true;
			}
		}	
	}
}

// Clears all game objects
void Snake::quit() {
	cout << "Snake::quit\n";
	
	delete snakeHead;
	delete apple;
	delete map;
	delete retryScreen;
	delete gameWindow;
	
	gameTitle = nullptr;
	snakeHead = nullptr;
	apple = nullptr;
	map = nullptr;
	retryScreen = nullptr;
	gameWindow = nullptr;

	tailSize = 0;
	appleFrame = 0;
	snakeBody.clear();
	gameObjects.clear();
	
}

// Snake destructor
Snake::~Snake() {
	cout << "Snake::~Snake\n";
	Snake::quit();
}