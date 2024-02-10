#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(const char* title, SDL_Rect rect) {
	cout << "GameWindow::GameWindow\n";
	windowRect = rect;
	gameTitle = title;
	window = nullptr;
	backgroundSurface = nullptr;
	windowTexture = nullptr;
	windowRen = nullptr;
	windowSurface = nullptr;
		
	//windowRen = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_SOFTWARE);
	//windowTexture = SDL_CreateTextureFromSurface(windowRen, windowSurface);
	//SDL_SetRenderDrawColor(windowRen, 0, 0, 200, 255);

	cout << "	Window created\n";
}

bool GameWindow::init() {
	cout << "GameWindow::init()\n";
	
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow(gameTitle, windowRect.x, windowRect.y, windowRect.w, windowRect.h, SDL_WINDOW_SHOWN);
		
		//Create window
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			windowSurface = SDL_GetWindowSurface(window);
		}
			
		return success;
	}
	
}

void GameWindow::loadObject(GameObject* object, SDL_Rect* imageCropAndPosition)
{
	
	//Load splash image
	object->objectSurface = SDL_LoadBMP(object->getTextureFile());

	if (object->objectSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", object->getTextureFile(), SDL_GetError());
	}
	
	
	
	//windowRect = SDL_Rect{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500 };
	if (SDL_BlitScaled(object->objectSurface, NULL, windowSurface, object->getRect()) < 0)
	{
		cout << "blit error: " << SDL_GetError() << endl;
	}
	else
	{
		//cout << "no blit error: " << object->getTextureFile() << ": x = " << object->getRect()->x
			//<< ", y = " << object->getRect()->y << ", w = " << object->getRect()->w
			//<< ", h = " << object->getRect()->h << endl;
	}

	if (SDL_UpdateWindowSurface(window) < 0)
	{
		cout << "update error: " << SDL_GetError() << endl;
	}

	//cout << "image loaded" << endl;
}

bool GameWindow::eventHandler() {
	//cout << "polling started" << endl;
	SDL_Event e;
	bool running = true;

	if (SDL_PollEvent(&e))
	{
		//cout << "Polling" << endl;
		if (e.type == SDL_QUIT)
		{	
			cout << "quitting" << endl;
			running = false;
		}
	}


	return running;
}

void GameWindow::addToRenderer(const char* file, SDL_Rect rect) {
	//cout << "RENDER: " << file << endl;

	//swap renderers 
	SDL_Texture* t = SDL_CreateTextureFromSurface(windowRen, IMG_Load(file));
	
	SDL_RenderCopy(windowRen, t, NULL, &rect);
	SDL_DestroyTexture(t);
	t = nullptr;
	
	

}

void GameWindow::present() {
	SDL_RenderPresent(windowRen);
	SDL_RenderClear(windowRen);
	
}

GameWindow& GameWindow::operator=(const GameWindow& other) {
	if(this->window != other.window){
		SDL_DestroyWindow(this->window);
		SDL_DestroyRenderer(this->windowRen);
		this->window = nullptr;
		this->windowRen = nullptr;
	}
	this->window = other.window;
	this->windowRen = other.windowRen;
	this->gameTitle = other.gameTitle;
	this->windowRect = other.windowRect;

	return *this;
}

void GameWindow::deleteWindow() {
	SDL_DestroyRenderer(windowRen);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(windowSurface);

	windowSurface = nullptr;
	gameTitle = nullptr;
	windowRen = nullptr;
	window = nullptr;

	SDL_Quit();
}

GameWindow::~GameWindow() {
	this->deleteWindow();
}
