#pragma once
#include <SDL.h>
#include <SDL_image.h>
//#include "Game.h"

//enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
using namespace std;

class GameWindow
{
	//friend class Game;
private:
	SDL_Window* gameWindow;
	
	//Game::Direction currentDirection;
public:
	SDL_Renderer* currentRen;
	SDL_Renderer* gameRen;
	
	static int g_width;
	static int g_height;
	int g_x;
	int g_y;
	const char* gametitle;
	

	GameWindow(const char* title = " ", int h = 640, int w = 640, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
	bool init(const char* file, SDL_Rect* rect = NULL);
	bool eventHandler();
	void addToRenderer(const char* file, SDL_Rect rect = { 0,0,g_width,g_height });
	void present();
	void deleteWindow();
	~GameWindow();

	GameWindow& operator=(const GameWindow& other);




};

