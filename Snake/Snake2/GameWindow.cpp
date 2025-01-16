#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(const char* title, SDL_Rect rect) {
	cout << "GameWindow::GameWindow()\n";
	windowRect = rect;
	gameTitle = title;
	window = nullptr;
	windowSurface = nullptr;

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

bool GameWindow::loadGameObject(GameObject* object, SDL_Rect* imageCropAndPosition)
{
	cout << "GameWindow::loadGameObject()\n";

	
	//Load splash image
	object->setSurface(SDL_LoadBMP(object->getTextureFile()));

	if (object->getSurface() == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", object->getTextureFile(), SDL_GetError());
		return false;
		
	}
	
	
	
	//windowRect = SDL_Rect{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500 };
	if (SDL_BlitScaled(object->getSurface(), NULL, windowSurface, object->getRect()) < 0)
	{
		cout << "object: " << object->getTextureFile() << " -- blit error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		//cout << "no blit error: " << object->getTextureFile() << ": x = " << object->getRect()->x
			//<< ", y = " << object->getRect()->y << ", w = " << object->getRect()->w
			//<< ", h = " << object->getRect()->h << endl;
	}

	if (SDL_UpdateWindowSurface(window) < 0)
	{
		cout << "object: " << object->getTextureFile() << " -- update error: " << SDL_GetError() << endl;
		return false;
	}

	//cout << "image loaded" << endl;
}

bool GameWindow::loadTextObject(TextObject* text)
{
	cout << "GameWindow::loadTextObject()\n";

	if (SDL_BlitSurface(text->getSurface(), NULL, windowSurface, text->getRect()) < 0)
	{
		cout << "text: " << text->getText() << " -- blit error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		//cout << "no blit error: " << object->getTextureFile() << ": x = " << object->getRect()->x
			//<< ", y = " << object->getRect()->y << ", w = " << object->getRect()->w
			//<< ", h = " << object->getRect()->h << endl;
	}

	if (SDL_UpdateWindowSurface(window) < 0)
	{
		cout << "object: " << text->getText() << " -- update error: " << SDL_GetError() << endl;
		return false;
	}

}

bool GameWindow::eventHandler() {
	//cout << "polling started" << endl;
	cout << "GameWindow::eventHandler()\n";

	SDL_Event e;
	bool quitting = false;

	if (SDL_PollEvent(&e))
	{
		//cout << "Polling" << endl;
		if (e.type == SDL_QUIT)
		{	
			cout << "quitting" << endl;
			quitting = true;
		}
	}


	return quitting;
}

GameWindow& GameWindow::operator=(const GameWindow& other) {
	cout << "GameWindow::op=()\n";

	if(this->window != other.window){
		SDL_DestroyWindow(this->window);
		this->window = nullptr;
	}
	this->window = other.window;
	this->gameTitle = other.gameTitle;
	this->windowRect = other.windowRect;

	return *this;
}

void GameWindow::deleteWindow() {
	cout << "GameWindow::deleteWindow()\n";
	SDL_FreeSurface(windowSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

GameWindow::~GameWindow() {
	cout << "GameWindow::~GameWindow()\n";

	this->deleteWindow();
}
