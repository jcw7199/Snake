#include "Snake.h"

Snake::Snake(){
	cout << "Snake::Snake()\n";
	srand(time(NULL));
	gameInstance = new Game("Snake", s_head);
	screenWidth = gameInstance->g_window->g_width;
	screenHeight = gameInstance->g_window->g_height;
	int center_x = screenWidth / 2;
	int center_y = screenHeight / 2;
	lastDir = Direction::NONE;
	app_r = { 0,0,s_dimensions * 2,s_dimensions * 2 };
	s_r = { center_x,center_y,s_dimensions,s_dimensions };

	apple = new GameObject(&app_r, "images/apple/1.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	s_head = new GameObject(&s_r, "images/head.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	s_tail = new GameObject(&s_r, "images/tail.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	background = new GameObject(nullptr, "images/map.png", MOVEMENT_TYPE::STATIC, Direction::NONE);


	respawnApple();
	gameInstance->g_player = s_head;
	gameInstance->objs.push_back(s_head);
	gameInstance->objs.push_back(apple);
	
}

void Snake::start() {
	cout << "Snake::start\n";
	while (gameInstance->isRunning) {
		
		gameInstance->isRunning = Snake::gameEvents();
		//cout << "	running\n";
		//update moving objects
		backwardsCheck();
		gameInstance->moveObject(*s_head);
		gameInstance->g_window->addToRenderer(background->getTextureFile());
		for (int i = 0; i < gameInstance->objs.size(); i++) {
			//cout << "	" << gameInstance->objs[i]->getTextureFile() << endl;
			gameInstance->g_window->addToRenderer(gameInstance->objs[i]->getTextureFile(), gameInstance->objs[i]->getRect());
			
		}

		for (int i = 0; i < s_body.size(); i++) {
			gameInstance->g_window->addToRenderer(s_tail->getTextureFile(), s_body[i]);
		}

		gameInstance->g_window->present();
		SDL_Delay(1000 / 30);

	}   
}

bool Snake::gameEvents() {
	//cout << "Snake::gameEvents()\n";
	bool running = gameInstance->gameEvents();
	if (running) {
		if (gameInstance->collisionDetection(*apple, *s_head) == true) {
			addTail();
			respawnApple();
		}
		moveSnake();
		animateApple();
		if (borderDetection() == true)
			running = gameOver();
		
	}
	return running;
}

void Snake::backwardsCheck() {
	if (   (lastDir == Direction::UP && s_head->getDir() == Direction::DOWN)
		|| (lastDir == Direction::DOWN && s_head->getDir() == Direction::UP)
		|| (lastDir == Direction::LEFT && s_head->getDir() == Direction::RIGHT)
		|| (lastDir == Direction::RIGHT && s_head->getDir() == Direction::LEFT)
		) {
		s_head->setDir(lastDir);
	}
	else {
		lastDir = s_head->getDir();
	}
}
void Snake::moveSnake() {
	//cout << "Snake::moveSnake()\n";
	
	for (int i = 0; i < tailSize - 1; i++) {
		
		s_body[i] = s_body[i + 1];
		
	}
	gameInstance->moveObject(*s_head);
	if(tailSize > 0)
		s_body[tailSize - 1] = s_head->getRect();


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
	
	x = rand() % (screenWidth - s_dimensions * 2);
	y = rand() % (screenHeight - s_dimensions * 2);
	

	apple->setRect({ x, y, s_dimensions * 2, s_dimensions * 2 });


}

void Snake::addTail() {
	//cout << tailSize << " Snake::addTail()\n";
	SDL_Rect tailRect{ 0, 0, s_dimensions, s_dimensions };
	SDL_Rect tempRect;
	if (tailSize == 0) {
		tempRect = s_head->getRect();
	}
	else {
		tempRect = s_body[tailSize - 1];
	}
	switch (s_head->getDir()) {
		case Direction::UP:
			tailRect.x = tempRect.x;
			tailRect.y = tempRect.y - s_dimensions;
			break;								 
												 
		case Direction::DOWN:					 
			tailRect.x = tempRect.x;			 
			tailRect.y = tempRect.y + s_dimensions;
			break;								  
												  
		case Direction::LEFT:					  
			tailRect.x = tempRect.x - s_dimensions;
			tailRect.y = tempRect.y;
			break;

		case Direction::RIGHT:
			tailRect.x = tempRect.x + s_dimensions;
			tailRect.y = tempRect.y;
			break;

		default:
			break;
	}
	//cout << s_head->getRect().x << ", " << s_head->getRect().y << " newTail: " << tailRect.x << ", " << tailRect.y << endl;
	tailSize++;
	s_body.push_back(tailRect);
	s_tail->setRect(tailRect);
	
}

bool Snake::borderDetection() {

	if (s_head->getRect().x == 0 && s_head->getDir() == Direction::LEFT)
		return true;

	if (s_head->getRect().x + s_dimensions == screenWidth && s_head->getDir() == Direction::RIGHT)
		return true;


	if (s_head->getRect().y == 0 && s_head->getDir() == Direction::UP)
		return true;

	if (s_head->getRect().y + s_dimensions == screenHeight && s_head->getDir() == Direction::DOWN)
		return true;

	return false;
}

bool Snake::gameOver() {
	cout << "Snake::GameOver()\n";
	SDL_Event e;
	
	s_body.clear();
	s_head->setRect({ screenWidth / 2, screenHeight / 2, s_dimensions, s_dimensions });
	s_head->setDir(Direction::NONE);
	tailSize = 0;
	//s_body.push_back(s_head->getRect());
	respawnApple();
	gameInstance->g_window->present();
	gameInstance->g_window->addToRenderer("images/game_over.png");
	gameInstance->g_window->present();
	bool quit = true;
	while (quit) {
		while (SDL_PollEvent(&e) > 0) {
			gameInstance->g_window->addToRenderer("images/game_over.png");
			gameInstance->g_window->present();

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
	
	s_body.empty();

	gameInstance->quit(); //will handle 
}

Snake::~Snake() {
	cout << "Snake::~Snake\n";
	Snake::quit();
}