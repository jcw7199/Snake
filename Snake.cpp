#include "Snake.h"

Snake::Snake(){
	cout << "Snake::Snake()\n";
	gameInstance = new Game("Snake", s_head);
	int center_x = gameInstance->g_window->g_width / 2;
	int center_y = gameInstance->g_window->g_height / 2;
	s_r = { center_x,center_y,snakeDimensions,snakeDimensions };
	s_head = new GameObject(&s_r, "images/head.png", MOVEMENT_TYPE::CONSTANT, Direction::NONE);
	gameInstance->g_player = s_head;
	
	cout << "	ooo\n";
	cout << "	" << s_head->getID() << " s_head\n";
	cout << "	" << gameInstance->g_player->getID() << " g_player\n";
	app_r = { 0,0,snakeDimensions,snakeDimensions };

	background = new GameObject(nullptr, "images/map.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	cout << "	" << background->getID() << " background\n";

	apple = new GameObject(&app_r, "images/apple/1.png", MOVEMENT_TYPE::STATIC, Direction::NONE);
	cout << "	" << apple->getID() << " apple\n";

	s.push_back(s_head);
	s.front() = s_head;
	tailSize = 1;
	appleFrame = 1;
	
	//gameInstance->objs.push_back(background);
	gameInstance->objs.push_back(s_head);
	gameInstance->objs.push_back(apple);
	//gameInstance->objs.front() = background;

	srand(time(NULL));

	cout << "	" << s_head->getID() << " " << gameInstance->objs.front()->getID();

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
	//cout << "Snake::moveSnake()\n";
	for (int i = 0; i < tailSize - 1; i++) {
		
		s[i] = s[i + 1];
		
	}
	gameInstance->moveObject(*s_head);
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

	apple->setRect({ x, y, snakeDimensions * 2, snakeDimensions * 2 });


}

void Snake::addTail() {
	cout << tailSize << " Snake::addTail()\n";
	SDL_Rect tailRect{ 0, 0, snakeDimensions, snakeDimensions };
	switch (s.front()->getDir()) {
		case Direction::UP:
			cout << "ummmmm\n";
			tailRect.x = s[tailSize - 1]->getRect().x;
			tailRect.y = s[tailSize - 1]->getRect().y - snakeDimensions;
			break;

		case Direction::DOWN:
			tailRect.x = s[tailSize - 1]->getRect().x;
			tailRect.y = s[tailSize - 1]->getRect().y + snakeDimensions;
			break;

		case Direction::LEFT:
			tailRect.x = s[tailSize - 1]->getRect().x - snakeDimensions;
			tailRect.y = s[tailSize - 1]->getRect().y;
			break;

		case Direction::RIGHT:
			tailRect.x = s[tailSize - 1]->getRect().x + snakeDimensions;
			tailRect.y = s[tailSize - 1]->getRect().y;
			break;

		default:
			break;
	}

	GameObject* newTail = new GameObject(&s_r, "tail.png", MOVEMENT_TYPE::DYNAMIC, Direction::NONE);
	tailSize++;
	s.push_back(newTail);
	gameInstance->objs.push_back(newTail);
}

void Snake::quit() {
	cout << "Snake::quit\n";
	for (int i = 0; i < s.size(); i++) {
		s[i]->destroyObject();
		delete s[i];
		s[i] = nullptr;
	}
	s.empty();

	gameInstance->quit(); //will handle 
}

Snake::~Snake() {
	cout << "Snake::~Snake\n";
	Snake::quit();
}