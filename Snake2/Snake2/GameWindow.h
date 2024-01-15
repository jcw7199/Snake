#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
//#include "Game.h"

//enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
using namespace std;

class GameWindow
{
	//friend class Game;
	
	//Game::Direction currentDirection;
public:
	SDL_Window* gameWindow;
	SDL_Renderer* windowRen;
	SDL_Surface* windowSurface;
	SDL_Surface* backgroundSurface;
	SDL_Surface* imageSurface;
	SDL_Texture* windowTexture;
	SDL_Rect* windowRect;

	const char* gameTitle;
	
	GameWindow(const char* title = " ", const char* backgroundImage = "", SDL_Rect rect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640});

	
	bool init();
	bool loadObject(GameObject object);
	bool eventHandler();
	void addToRenderer(const char* file, SDL_Rect rect);
	void present();
	void deleteWindow();
	~GameWindow();

	GameWindow& operator=(const GameWindow& other);




};

