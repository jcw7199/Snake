#include "Snake.h"

Snake::Snake() : Game("Snake", snakeHead, map, mapRect)
{ 

	cout << "Snake::Snake()\n";
	srand(time(NULL));
	
	
	SDL_Surface* mapSurface = SDL_LoadBMP("images/map.bmp");
	mapRect = SDL_Rect{ 0, 0, mapSurface->w, mapSurface->h };
	windowRect = SDL_Rect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mapSurface->w, mapSurface->h };
	
	int center_x = mapRect.w / 2;
	int center_y = mapRect.h / 2;
	lastDirection = Direction::NONE;
	appleRect = { 0,0,snakeBodyDimensions * 2,snakeBodyDimensions * 2 };
	snakeRect = { center_x, center_y, snakeBodyDimensions,snakeBodyDimensions };

	apple = new GameObject(appleRect, "images/apple/1.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	snakeHead = new GameObject(snakeRect, "images/head.bmp", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	snakeTail = new GameObject(snakeRect, "images/tail.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	map = new GameObject(mapRect, "images/map.bmp", MOVEMENT_TYPE::STATIC, Direction::NONE);

	gamePlayer = snakeHead;
	gameTitle = "Snake Game";
 
	gameObjects.push_back(snakeHead);
	gameObjects.push_back(apple);	
	
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
	gameWindow = new GameWindow("Hello World", windowRect);


	gameWindow->init();
	gameWindow->loadObject(map);
	gameWindow->loadObject(snakeHead);
	
	gameWindow->eventHandler();
	gameWindow->deleteWindow();

}

bool Snake::gameEvents() {
	SDL_Event e;
	bool running = true;
	lastDirection = snakeHead->getDir();

	if (SDL_PollEvent(&e) > 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					gamePlayer->setDir(Direction::UP);
					break;

				case SDLK_DOWN:
					gamePlayer->setDir(Direction::DOWN);
					break;

				case SDLK_LEFT:
					gamePlayer->setDir(Direction::LEFT);
					break;

				case SDLK_RIGHT:
					gamePlayer->setDir(Direction::RIGHT);
					break;

				case SDLK_q:
					quit();
					running = false;

				default:
					gamePlayer->setDir(Direction::NONE);
					break;
				}

			}
			else {
				return gameWindow->eventHandler();
			}
		}

	if (appleCollision() == true)
	{
		addTail();
		respawnApple();
	}
	if (backwardsCheck() == false)
	{
		moveBody();
		lastDirection = snakeHead->getDir();
	}
	else
	{
		snakeHead->setDir(lastDirection);
	}
	
	animateApple();

	if (borderCollision() == true)
	{
		running = false;
	}

	return running;
}

bool Snake::backwardsCheck() {
	if (   
		   (snakeHead->getDir() == Direction::UP && lastDirection == Direction::DOWN)
		|| (snakeHead->getDir() == Direction::DOWN && lastDirection == Direction::UP)
		|| (snakeHead->getDir() == Direction::LEFT && lastDirection == Direction::RIGHT)
		|| (snakeHead->getDir() == Direction::RIGHT && lastDirection == Direction::LEFT)
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
	SDL_Rect snakeRect = *snakeHead->getRect();
	switch (snakeHead->getDir())
	{
		case Direction::UP:
			snakeRect.y += 5;
			snakeHead->setRect(snakeRect);
			break;

		case Direction::DOWN:
			snakeRect.y -= 5;
			snakeHead->setRect(snakeRect);
			break;

		case Direction::LEFT:
			snakeRect.x -= 5;
			snakeHead->setRect(snakeRect);
			break;

		case Direction::RIGHT:
			snakeRect.x += 5;
			snakeHead->setRect(snakeRect);
			break;

		default:
			break;
	}
}

void Snake::moveBody() {
	//cout << "Snake::moveSnake()\n";
	
	for (int i = 0; i < tailSize - 1; i++) {
		
		snakeBody[i] = snakeBody[i + 1];
		
	}
	
	moveHead();

}

void Snake::animateApple() {
	switch (appleFrame) {
	case 1:
		apple->setTexture("images/apple/1.png");
		break;
	case 5:				   
		apple->setTexture("images/apple/2.png");
		break;			   
	case 9:		
		apple->setTexture("images/apple/3.png");
		break;
	}

	appleFrame++;
	if (appleFrame > 5)
		appleFrame = 1;
}

void Snake::respawnApple() {
	int x, y = 0;
	
	x = rand() % (screenWidth - snakeBodyDimensions * 2);
	y = rand() % (screenHeight - snakeBodyDimensions * 2);
	

	apple->setRect({ x, y, snakeBodyDimensions * 2, snakeBodyDimensions * 2 });


}

void Snake::addTail() {
	//cout << tailSize << " Snake::addTail()\n";
	SDL_Rect tailRect{ 0, 0, snakeBodyDimensions, snakeBodyDimensions };
	SDL_Rect tempRect;
	if (tailSize == 0) {
		tempRect = *snakeHead->getRect();
	}
	else {
		tempRect = *snakeBody[tailSize - 1]->getRect();
	}
	switch (snakeHead->getDir()) {
		case Direction::UP:
			tailRect.x = tempRect.x;
			tailRect.y = tempRect.y - snakeBodyDimensions;
			break;								 
												 
		case Direction::DOWN:					 
			tailRect.x = tempRect.x;			 
			tailRect.y = tempRect.y + snakeBodyDimensions;
			break;								  
												  
		case Direction::LEFT:					  
			tailRect.x = tempRect.x - snakeBodyDimensions;
			tailRect.y = tempRect.y;
			break;

		case Direction::RIGHT:
			tailRect.x = tempRect.x + snakeBodyDimensions;
			tailRect.y = tempRect.y;
			break;

		default:
			break;
	}
	//cout << s_head->getRect().x << ", " << s_head->getRect().y << " newTail: " << tailRect.x << ", " << tailRect.y << endl;
	tailSize++;
	GameObject * newTail = new GameObject(tailRect, "images/tail.png");
	snakeBody.push_back(newTail);
	snakeTail->setRect(tailRect);
	
}

bool Snake::appleCollision()
{
	if (SDL_RectEquals(snakeHead->getRect(), apple->getRect()))
	{
		return true;
	}

	return false;
}

bool Snake::borderCollision() { 

	if (snakeHead->getRect()->x == 0 && snakeHead->getDir() == Direction::LEFT)
		return true;

	if (snakeHead->getRect()->x + snakeBodyDimensions == screenWidth && snakeHead->getDir() == Direction::RIGHT)
		return true;


	if (snakeHead->getRect()->y == 0 && snakeHead->getDir() == Direction::UP)
		return true;

	if (snakeHead->getRect()->y + snakeBodyDimensions == screenHeight && snakeHead->getDir() == Direction::DOWN)
		return true;

	return false;
}

bool Snake::gameOver() {
	cout << "Snake::GameOver()\n";
	SDL_Event e;
	
	snakeBody.clear();
	snakeHead->setRect({ screenWidth / 2, screenHeight / 2, snakeBodyDimensions, snakeBodyDimensions });
	snakeHead->setDir(Direction::NONE);
	tailSize = 0;
	//s_body.push_back(s_head->getRect());
	respawnApple();
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

	gameInstance->quit(); //will handle 
}

Snake::~Snake() {
	cout << "Snake::~Snake\n";
	Snake::quit();
}