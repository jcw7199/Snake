#include "GameWindow.h"
#include <iostream>

int GameWindow::g_width = 640;
int GameWindow::g_height = 640;

GameWindow::GameWindow(const char* title, int h, int w, int x, int y) {
	cout << "GameWindow::GameWindow\n";
	g_width = w;
	g_height = h;
	g_x = x;
	g_y = y;
	gametitle = title;
	gameWindow = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	gameRen = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_SOFTWARE);
	
	SDL_SetRenderDrawColor(gameRen, 0, 0, 200, 255);
	SDL_SetRenderDrawColor(currentRen, 200, 0, 0, 255);

	currentRen = gameRen;
	cout << "	Window created\n";
	
	
}

bool GameWindow::init(const char* file, SDL_Rect* rect) {
	cout << "GameWindow::init()\n";
	
	//SDL_Texture* t =  SDL_CreateTextureFromSurface(gameRen, IMG_Load(file));
	
	bool running = true;
	while (running) {
		running = eventHandler();
		addToRenderer(file, *rect);
	
		//SDL_RenderCopy(gameRen, t, NULL, rect);
		//SDL_RenderPresent(gameRen);
		//SDL_RenderClear(gameRen);
		present();
		
	}
	return false;
}

bool GameWindow::eventHandler() {
	
	SDL_Event e;
	
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		default:
			break;
		}
	}

	return true;
}

void GameWindow::addToRenderer(const char* file, SDL_Rect rect) {
	//cout << "RENDER: " << file << endl;

	//swap renderers 
	SDL_Texture* t = SDL_CreateTextureFromSurface(gameRen, IMG_Load(file));
	
	SDL_RenderCopy(gameRen, t, NULL, &rect);
	SDL_DestroyTexture(t);
	t = nullptr;
	
	

}

void GameWindow::present() {
	SDL_RenderPresent(currentRen);
	SDL_RenderClear(currentRen);
	
}

GameWindow& GameWindow::operator=(const GameWindow& other) {
	if(this->gameWindow != other.gameWindow){
		SDL_DestroyWindow(this->gameWindow);
		SDL_DestroyRenderer(this->gameRen);
		this->gameWindow = nullptr;
		this->gameRen = nullptr;
	}
	this->gameWindow = other.gameWindow;
	this->gameRen = other.gameRen;
	this->gametitle = other.gametitle;
	this->g_height = other.g_height;
	this->g_width = other.g_width;
	this->g_x = other.g_x;
	this->g_y = other.g_y;

	return *this;
}

void GameWindow::deleteWindow() {
	SDL_DestroyRenderer(gameRen);
	SDL_DestroyWindow(gameWindow);
	gametitle = nullptr;
	gameRen = nullptr;
	gameWindow = nullptr;
}

GameWindow::~GameWindow() {
	this->deleteWindow();
}
