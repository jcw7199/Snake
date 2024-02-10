#include "Snake.h"

using namespace std;

Snake::Snake()
{ 
	cout << "Snake::Snake()\n";
	srand(time(NULL));
	gamePlayer = snakeHead;
	gameTitle = "Snake Game";

	gameWindow = new GameWindow(gameTitle, windowRect);


	//gameObjects.push_back(gamePlayer);
 
	tailSize = 1;
	
	isRunning = true;
	respawnApple();
}

void Snake::start() {
	cout << "Snake::start\n";
	//initialize background
	
	//GameObject map = GameObject(mapRect, "images/map.bmp");
	//
	//SDL_Surface* temp = SDL_LoadBMP("images/head.bmp");
	//SDL_Rect tempRect = SDL_Rect{ 250, 250, temp->w, temp->h };
	//GameObject head = GameObject(tempRect, "images/head.bmp");
	//initialize game window
	//gameWindow = new GameWindow("Hello World", windowRect);
	

	gameWindow->init();
	gameObjects.push_back(map);
	gameObjects.push_back(apple);
	gameObjects.push_back(snakeHead);
	snakeBody.push_back(snakeHead);

	loadGameObjects();
	gameEvents();
	gameWindow->deleteWindow();

}

bool Snake::gameEvents() {
	cout << "Snake::Game events()" << endl;
	SDL_Event e;
	bool running = true;
	//lastDirection = snakeHead.getDir();
	while (running == true)
	{
		if (SDL_PollEvent(&e) > 0) {
			//cout << "snake: " << snakeHead.getRect()->x << ", " << snakeHead.getRect()->y << endl;
			//cout << "apple: " << apple.getRect()->x << ", " << apple.getRect()->y << endl;
			if (running == false)
			{
				break;
			}
			if (e.type == SDL_KEYDOWN) {
				cout << "key down" << endl;

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

				case SDLK_q:
					cout << "quitting" << endl;
					running = false;
					break;

				default:
					break;
				}
				
				if (backwardsCheck() == true)
				{
					cout << "backwards movement detected." << endl;
					snakeBody.front()->nextDirection = snakeBody.front()->currentDirection;
				}
				else
				{
					//snakeHead.setDir(nextDirection);
				}

				animateApple();
			}
			else
			{
				running = gameWindow->eventHandler();
				
				//cout << "no key down" << endl;	
			}
		}

		if (appleCollision() == true)
		{
			cout << "apple collision detected." << endl;
			snakeBody.front()->printRect();
			//SDL_TriggerBreakpoint();
			addTail();
			respawnApple();
		}

		if (borderCollision() == true)
		{
			cout << "border collision detected." << endl;			
			snakeBody.front()->printRect();

			running = false;
		}
		
		
		moveBody();		

		SDL_Delay(50);		
		loadGameObjects();


	}
	return running;
}

bool Snake::backwardsCheck() {
	cout << "Snake::backwardscheck()" << endl;

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

void Snake::moveHead()
{
	// set head direction, so snake can move together.
	cout << "move body part" << endl;
	//body needs the direction of the head before the head changes direction
	snakeBody.front()->lastDirection = snakeBody.front()->currentDirection;
	switch (snakeBody.front()->nextDirection)
	{
	case Direction::UP:
		cout << "moving up" << endl;
		snakeBody.front()->getRect()->y -= snakeVelocity;
		snakeBody.front()->currentDirection = Direction::UP;
		break;

	case Direction::DOWN:
		cout << "moving down" << endl;
		snakeBody.front()->getRect()->y += snakeVelocity;
		snakeBody.front()->currentDirection = Direction::DOWN;
		break;

	case Direction::LEFT:
		cout << "moving left" << endl;
		snakeBody.front()->getRect()->x -= snakeVelocity;
		snakeBody.front()->currentDirection = Direction::LEFT;
		break;

	case Direction::RIGHT:
		cout << "moving right" << endl;
		snakeBody.front()->getRect()->x += snakeVelocity;
		snakeBody.front()->currentDirection = Direction::RIGHT;
		break;

	case Direction::NONE:
		cout << "moving none" << endl;
		break;
	default:
		break;
	}
	
	snakeBody.front()->setDir(snakeBody.front()->currentDirection);
	
	//SDL_TriggerBreakpoint();
	//SDL_FreeSurface(snakeHead.objectSurface);
	//SDL_UpdateWindowSurface(gameWindow->window);
	//if(tailSize > 1 )
		//moveBody();

	//SDL_TriggerBreakpoint();
	//lastDirection = snakeHead.getDir();
}

void Snake::moveBody()
{
	//cout << "\n--------------------------\n";
	//cout << "Snake::moveBody\n";
	//lastDirection = nextDirection;
	list<SnakeBodyPart*>::reverse_iterator rev_it;
	list<SnakeBodyPart*>::reverse_iterator prevIt;
	
	//list<SnakeBodyPart*>::iterator it;
	//list<SnakeBodyPart*>::iterator nextIt;

	SnakeBodyPart* previous;
	SnakeBodyPart* current;
	//SnakeBodyPart* next;
	
	SDL_Rect previousRect = *snakeBody.front()->getRect();
	Direction previousDir = snakeBody.front()->getDir();
	
	SDL_Rect currentRect;
	Direction currentDir;

	//moveHead();
	
	
	/*
	if (tailSize > 1)
	{
		it = std::next(snakeBody.begin(), 1);

		while (it != snakeBody.end())
		{		
			current = *it;
			currentRect = *current->getRect();
			currentDir = current->getDir();

			current->setRect(previousRect);
			current->setDir(previousDir);

			
			
			previousRect = currentRect;
			previousDir = currentDir;
			std::advance(it, 1);
		}

	}
	*/
	for (rev_it = snakeBody.rbegin(); rev_it != snakeBody.rend(); ++rev_it)
	{
		prevIt = next(rev_it, 1);
		current = *rev_it;
		if (prevIt != snakeBody.rend())
		{
			previous = *prevIt;

			current->nextDirection = previous->currentDirection;			
			current->lastDirection = current->currentDirection;
			current->nextDirection = previous->lastDirection;

			current->setRect(*previous->getRect());
		}
		else
		{
			moveHead();
		}

	}
	

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
}

void Snake::animateApple()
{
	switch (appleFrame) {
	case 1:
		apple->setTexture("images/apple/1.bmp");
		break;
	case 5:				   
		apple->setTexture("images/apple/2.bmp");
		break;			   
	case 9:		
		apple->setTexture("images/apple/3.bmp");
		break;
	}

	appleFrame++;
	if (appleFrame > 9)
		appleFrame = 1;
}

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

void Snake::addTail() {
	cout << tailSize << " Snake::addTail()\n";
	//SDL_TriggerBreakpoint();

	SDL_Rect newTailRect = SDL_Rect{ 0, 0, 0, 0 };
	SnakeBodyPart* currentTail = snakeBody.back();
	Direction newTailDirection = Direction::NONE;
	

	SDL_Rect tailRect = *currentTail->getRect();
	switch (currentTail->currentDirection)
	{
	case Direction::UP:
		cout << "direction up, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x,
								tailRect.y + snakeBodyDimensions,
								tailRect.w, tailRect.h };
		break;

	case Direction::DOWN:
		cout << "direction down, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x,
								tailRect.y - snakeBodyDimensions,
								tailRect.w, tailRect.h };
		break;

	case Direction::LEFT:
		cout << "direction left, add tail" << endl;
		newTailRect = SDL_Rect{
								tailRect.x + snakeBodyDimensions,
								tailRect.y,
								tailRect.w, tailRect.h };
		break;

	case Direction::RIGHT:
		cout << "direction right, add tail" << endl;

		newTailRect = SDL_Rect{
								tailRect.x - snakeBodyDimensions,
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


	SnakeBodyPart* newTail = new SnakeBodyPart(newTailRect, "images/tail.bmp", MOVEMENT_TYPE::CONSTANT, newTailDirection);
	newTail->setDir(currentTail->currentDirection);
	newTail->currentDirection = Direction::NONE;
	newTail->lastDirection = Direction::NONE;
	newTail->nextDirection = currentTail->lastDirection;
	cout << "old tail: ";
	snakeBody.back()->printRect();
	
	gameObjects.push_back(newTail);
	snakeBody.push_back(newTail);
	tailSize++;
	cout << "tail size: " << snakeBody.size() <<" new tail: ";
	snakeBody.back()->printRect();
	//SDL_TriggerBreakpoint();
}

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

bool Snake::borderCollision() {

	if (snakeBody.front()->getRect()->x == 0)
	{
		cout << "left border" << endl;
		return true;
	}

	if (snakeBody.front()->getRect()->x + snakeBodyDimensions == screenWidth)
	{
		cout << "right border" << endl;
		return true;
	}

	if (snakeBody.front()->getRect()->y == 0)
	{
		cout << "up border" << endl;
		return true;
	}

	if (snakeBody.front()->getRect()->y + snakeBodyDimensions == screenHeight)
	{
		cout << "down border" << endl;
		return true;
	}
	return false;
}

bool Snake::bodyCollision()
{
	return true;
}

bool Snake::gameOver() {
	cout << "Snake::GameOver()\n";
	SDL_Event e;
	
	snakeBody.clear();
	snakeBody.front()->setRect({ screenWidth / 2, screenHeight / 2, snakeBodyDimensions, snakeBodyDimensions });
	snakeBody.front()->setDir(Direction::NONE);
	tailSize = 0;
	//s_body.push_back(s_head->getRect());
	gameWindow->present();
	gameWindow->addToRenderer("images/game_over.png", gameWindow->windowRect);
	gameWindow->present();
	bool quit = true;
	while (quit) {
		while (SDL_PollEvent(&e) > 0) {
			gameWindow->addToRenderer("images/game_over.png", gameWindow->windowRect);
			gameWindow->present();

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_q:
					return false;

				case SDLK_RETURN:
					return true;

				default:
					break;
				}
			}

		}
	}
}

void Snake::quit() {
	cout << "Snake::quit\n";
	
	snakeBody.empty();
}

Snake::~Snake() {
	cout << "Snake::~Snake\n";
	Snake::quit();
}