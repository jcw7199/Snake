#include "Game.h"

using namespace std;

Game::Game(const char* title, GameObject *player) {
	cout << "Game::Game()\n";
	//cout << player.getRect().x << endl;
	isRunning = true;
	g_title = title;
	g_window = new GameWindow(g_title);
	if (player != nullptr) {
		cout << "player " << player->getID() << " " << player->getTextureFile();
		g_player = player;
		cout << g_player->getID() << " " << g_player->getTextureFile();

		objs.push_back(g_player);
		
	}
	else {
		g_player = nullptr;
	}

	cout << "	Game created\n";
}

void Game::start() {
	cout << "Game::Start\n";
	cout << g_player->getTextureFile() << endl;
	cout << objs.size() << endl;
	while (isRunning) {
		//cout << "running\n";
		g_window->present();
		isRunning = gameEvents();
	
		//update moving objects
		moveObject(*g_player);
		//cout << "o\n";
		for (int i = 0; i < objs.size(); i++) {
			if(objs[i] != nullptr)
				g_window->addToRenderer(objs[i]->getTextureFile(), objs[i]->getRect());
		}
		
	}
}

void Game::quit(){
	cout << "Game::quit()\n";
	isRunning = false;
	g_player->destroyObject();
	g_window->deleteWindow();
	g_window = nullptr;
	g_title = nullptr;

	for (int i = 0; i < objs.size(); i++) {
			objs[i]->destroyObject();
	}
	objs.empty();
}

bool Game::gameEvents() {
	SDL_Event e;
	
	if (SDL_PollEvent(&e) > 0) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				g_player->setDir(Direction::UP);
				cout << "up\n";
				break;

			case SDLK_DOWN:
				g_player->setDir(Direction::DOWN);
				break;

			case SDLK_LEFT:
				g_player->setDir(Direction::LEFT);
				break;

			case SDLK_RIGHT:
				g_player->setDir(Direction::RIGHT);
				break;

			case SDLK_q:
				quit();
				return false;

			default:
				g_player->setDir(Direction::NONE);
				break;
			}

		}
		else {
			return g_window->eventHandler();
		}
	}

	return true;
}

void Game::moveObject(GameObject &obj) {
	//cout << "Game::moveObject(): " << obj.getID() << endl;
	SDL_Rect rect = obj.getRect();
	//cout << "ooooooO\n";

	switch (obj.getDir()) 
	{
	case Direction::UP:
		if (rect.y >= rect.h / 3)
			rect.y -= rect.h / 3;
		else
			rect.y = 0;
		break;

	case Direction::DOWN:
		if (rect.y + rect.h < g_window->g_height - rect.h / 3)
			rect.y += rect.h / 3;
		else
			rect.y = g_window->g_height - rect.h;
		break;

	case Direction::LEFT:
		if (rect.x >= rect.w / 3)
			rect.x -= rect.w / 3;
		else
			rect.x = 0;
		break;

	case Direction::RIGHT:
		if (rect.x + rect.w < g_window->g_width - rect.w / 3)
			rect.x += rect.w / 3;
		else
			rect.x = g_window->g_width - rect.w;
		break;
	default:
		break;
	}
	//cout << "lololol\n";
	obj.setRect(rect);
	//cout << "fufuffu\n";
	if (obj.getMVMT() == MOVEMENT_TYPE::DYNAMIC)
		obj.setDir(Direction::NONE);
}

bool Game::collisionDetection(GameObject& obj1, GameObject& obj2) {
	int obj1_HOZ_Bounds[2] = { obj1.getRect().x, obj1.getRect().x + obj1.getRect().w };
	int obj1_VER_Bounds[2] = { obj1.getRect().y, obj1.getRect().y + obj1.getRect().h };

	int obj2_HOZ_Bounds[2] = { obj2.getRect().x, obj2.getRect().x + obj2.getRect().w };
	int obj2_VER_Bounds[2] = { obj2.getRect().y, obj2.getRect().y + obj2.getRect().h };
	
	if (obj1_HOZ_Bounds[0] >= obj2_HOZ_Bounds[0] && obj1_HOZ_Bounds[0] <= obj2_HOZ_Bounds[1])
		if (obj1_VER_Bounds[0] >= obj2_VER_Bounds[0] && obj1_VER_Bounds[0] <= obj2_VER_Bounds[1])
			return true;
		
	if (obj2_HOZ_Bounds[0] >= obj1_HOZ_Bounds[0] && obj2_HOZ_Bounds[0] <= obj1_HOZ_Bounds[1])
		if (obj2_VER_Bounds[0] >= obj1_VER_Bounds[0] && obj2_VER_Bounds[0] <= obj1_VER_Bounds[1])
			return true;
	

	
	return false;
}

Game::~Game() {
	this->quit();
}