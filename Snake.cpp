#include "Snake.h"

Snake::Snake(){
	cout << "Snake::Snake()\n";
	gameInstance = new Game("Snake", s_head);
	
	background = new GameObject(nullptr, "images/map.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	cout << "	" << background->getID() << " background\n";

	app_r = { 0,0,s_dimensions,s_dimensions };
	apple = new GameObject(&app_r, "images/apple/1.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	cout << "	" << apple->getID() << " apple\n";

	s_tail = new GameObject(&s_r, "images/tail.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	cout << "	" << s_tail->getID() << " tail\n";


	int center_x = gameInstance->g_window->g_width / 2;
	int center_y = gameInstance->g_window->g_height / 2;
	s_r = { center_x,center_y,s_dimensions,s_dimensions };
	s_head = new GameObject(&s_r, "images/head.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	gameInstance->g_player = s_head;
	cout << "	ooo\n";
	cout << "	" << s_head->getID() << " s_head\n";
	cout << "	" << gameInstance->g_player->getID() << " g_player\n";

	gameInstance->objs.push_back(s_head);
	gameInstance->objs.push_back(apple);
	
	srand(time(NULL));
}

void Snake::start() {
	cout << "Snake::start\n";
	while (gameInstance->isRunning) {
		
		gameInstance->isRunning = Snake::gameEvents();
		//cout << "	running\n";
		//update moving objects
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
			cout << "coll\n";
			addTail();
			respawnApple();
		}
		moveSnake();
		animateApple();
	}
	return running;
}

void Snake::moveSnake() {
	cout << "Snake::moveSnake()\n";
	
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
	case 2:				   
		apple->setTexture("images/apple/2.png");
		break;			   
	case 3:		
		apple->setTexture("images/apple/3.png");
		break;
	}

	appleFrame++;
	if (appleFrame > 3)
		appleFrame = 1;
}

void Snake::respawnApple() {
	int x, y = 0;
	//do {
		x = rand() % screenWidth;
		y = rand() % screenHeight;
	//} while (x % gameInstance->g_window->g_height != 0 && y % gameInstance->g_window->g_height != 0);

	apple->setRect({ x, y, s_dimensions * 2, s_dimensions * 2 });


}

void Snake::addTail() {
	cout << tailSize << "Snake::addTail()\n";
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
			cout << "ummmmm\n";
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
	cout << s_head->getRect().x << ", " << s_head->getRect().y << " newTail: " << tailRect.x << ", " << tailRect.y << endl;
	tailSize++;
	s_body.push_back(tailRect);
	s_tail->setRect(tailRect);
	
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