#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "TextObject.h"
//#include "Game.h"

//enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
using namespace std;

class GameWindow
{
	//friend class Game;
	
	//Game::Direction currentDirection;
public:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	SDL_Rect windowRect;

	const char* gameTitle;
	
	GameWindow(const char* title = " ", SDL_Rect windowSize = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640});

	
	bool init();
	bool loadGameObject(GameObject* object, SDL_Rect* imageCropAndPosition = nullptr);
	bool loadTextObject(TextObject* text);
	
	bool eventHandler();
	void deleteWindow();
	~GameWindow();

	GameWindow& operator=(const GameWindow& other);




};

