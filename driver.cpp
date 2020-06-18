#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Snake.h"
using namespace std;

//enum Direction { NONE, UP, DOWN, LEFT, RIGHT};
//
//SDL_Window* gameWindow;
//SDL_Renderer* gameRen;
//SDL_Surface* textureSurface;
//bool eventHandler();
//
//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 640;
//Direction currentDirection = Direction::NONE;
//vector<SDL_Rect> Snake;
//int tailSize = 0;
//
//
//SDL_Surface* loadSurface(const char* file, SDL_Rect* srcRect = nullptr, SDL_Rect* destRect = nullptr);
//SDL_Rect addTail();
//void MoveSnake(SDL_Rect* newHead);
//void printSnake();
//void draw();
//void render();
//SDL_Rect keepMoving();
//
//int c = 0;


int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL couldnt initialize\n";
		cout << SDL_GetError();
	}
	else {
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted & flags) != flags) {
			cout << "SDL_IMG could not initialize\n";
			cout << IMG_GetError();
		}
		else {
			cout << "??\n";
			//GameObject player = GameObject();
			//player.setTexture("head.png");
			//SDL_Window* dow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
			//
			//SDL_Renderer* ren = SDL_CreateRenderer(dow, -1, SDL_RENDERER_TARGETTEXTURE);
			//SDL_Surface* s = IMG_Load("images/tail.png");// SDL_LoadBMP("tail.bmp");
			//SDL_Texture* t = SDL_CreateTextureFromSurface(ren, s);
			SDL_Rect r{ 50,40,50,50 };
			SDL_Rect u{ 100,40,50,50 };
			SDL_Rect t{ 50,100,50,50 };
			//SDL_FreeSurface(s);
			//SDL_RenderCopy(ren, t, NULL, &r); 
			//SDL_RenderPresent(ren);
			//SDL_RenderClear(ren);
			//SDL_Delay(2000);
			//SDL_RenderPresent(ren);
			//SDL_Delay(2000);
			//SDL_DestroyWindow(dow);
			//SDL_DestroyRenderer(ren);
			//SDL_DestroyTexture(t);
			
			//GameObject player(&r, "images/tail.png", MOVEMENT_TYPE::DYNAMIC, Direction::NONE);
			/*GameWindow win("test");
			win.addToRenderer("images/map.png", NULL);
			win.addToRenderer("images/head.png", &r);
			win.addToRenderer("images/tail.png", &u);
			*/

			//win.present();
			//win.init("images/map.png", NULL);
			//cout << "jf\n";
			//SDL_Delay(2000);
			vector<int> insy;
			insy.push_back(0);
			insy.push_back(1);
			insy.push_back(2);
			insy.push_back(3);

			for (int var = 0; var < insy.size(); var++)
			{
				cout << insy[var] << endl;
			}
			Snake s = Snake(); //"idk", player);
			cout << "start\n";
			s.start();
			
			
		}
	}
	/*
		gameWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		gameRen = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_TARGETTEXTURE);
		SDL_SetRenderDrawColor(gameRen, 0, 0, 200, 255);
		
		
		bool isRunning = true;
		int FPS = 60;
		Uint32 runTimeStart;
		int runTime;
		int delay = 1000/FPS;
		int c = 0;

		//game loop
		while (isRunning == true)
		{
			//runTimeStart = SDL_GetTicks();
			
			render();
			isRunning = eventHandler();
			draw();
			
			
			
			if(currentDirection != Direction::NONE)
				MoveSnake(&keepMoving());
			
			SDL_Delay(100);
			//runTime = SDL_GetTicks() - runTimeStart;			
		}
		
	}
	
	SDL_DestroyRenderer(gameRen);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	
	*/
	
	return 0;
}

//bool eventHandler() {
//	SDL_Event e;
//
//	while (SDL_PollEvent(&e) > 0)
//	{
//		switch (e.type)
//		{
//		case SDL_QUIT:
//			return false;
//			break;
//
//		case SDL_KEYDOWN:
//			switch (e.key.keysym.sym) {
//			case SDLK_UP:
//				currentDirection = Direction::UP;
//				break;
//
//			case SDLK_DOWN:
//				currentDirection = Direction::DOWN;
//				break;
//
//			case SDLK_LEFT:
//				currentDirection = Direction::LEFT;
//				break;
//
//			case SDLK_RIGHT:
//				currentDirection = Direction::RIGHT;
//				break;
//
//			default:
//				currentDirection = Direction::NONE;
//				break;
//			}
//			addTail();
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	return true;
//}
//
//
//SDL_Rect addTail() {
//	SDL_Rect newTail;
//	newTail.h = 32;
//	newTail.w = 32;
//	cout << "adding\n";
//
//	if(tailSize == 0) {
//			newTail.x = 0; //end of snake coords.
//			newTail.y = 0; //ditto
//			Snake.push_back(newTail);
//			tailSize++;
//	}
//	else {
//		switch (currentDirection) {
//			case Direction::UP:
//				newTail.x = Snake[tailSize - 1].x;
//				newTail.y = Snake[tailSize - 1].y - 32;
//				break;
//
//			case Direction::DOWN:
//				newTail.x = Snake[tailSize - 1].x;
//				newTail.y = Snake[tailSize - 1].y + 32;
//				break;
//
//			case Direction::LEFT:
//				newTail.x = Snake[tailSize - 1].x - 32;
//				newTail.y = Snake[tailSize - 1].y;
//				break;
//
//			case Direction::RIGHT:
//				newTail.x = Snake[tailSize - 1].x + 32;
//				newTail.y = Snake[tailSize - 1].y;
//				break;
//
//			default:
//				break;
//		}
//		if (tailSize <= 5) {
//			Snake.push_back(newTail);
//			tailSize++;
//		}
//		else {
//			MoveSnake(&newTail);
//			printSnake();
//		}
//	}
//
//	std::cout << newTail.x << ", " << newTail.y << endl;
//	std::cout << tailSize << " : " << Snake.size() << endl;
//	return newTail;
//	
//	
//}
//
//SDL_Surface* loadSurface(const char* file, SDL_Rect* srcRect, SDL_Rect* destRect) {
//	 SDL_Surface *surface = SDL_GetWindowSurface(gameWindow);
//	SDL_Surface* image;
//	
//	if ((image = SDL_LoadBMP(file)) < 0) {
//		std::cout << "file not load";
//		return nullptr;
//	}
//	
//	
//	if (SDL_BlitScaled(image, srcRect, surface, destRect) < 0)
//		return nullptr;
//
//	return surface;
//}
//
//void render() {
//	SDL_RenderClear(gameRen);
//	draw();
//	SDL_RenderPresent(gameRen);
//}
//
//void draw() {
//	//
//
//	//Render background
//	textureSurface = SDL_LoadBMP("bg.bmp");
//	SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(gameRen, textureSurface);
//	SDL_FreeSurface(textureSurface);
//	SDL_RenderCopy(gameRen, bgTexture, NULL, NULL);
//	
//
//	//Render snake
//	textureSurface = SDL_LoadBMP("tail.bmp");
//	SDL_Texture* tailTexture = SDL_CreateTextureFromSurface(gameRen, textureSurface);
//	SDL_FreeSurface(textureSurface);
//
//
//	for (int i = 0; i < tailSize; i++) {
//		SDL_RenderCopy(gameRen, tailTexture, NULL, &Snake[i]);
//	}
//	
//}
//
//void MoveSnake(SDL_Rect* newHead) {
//	int tempX = 0;
//	int tempY = 0;
//	
//	for (int i = 0; i < tailSize-1; i++) {
//		Snake[i] = Snake[i + 1];
//	}
//	Snake[tailSize - 1].x = newHead->x;
//	Snake[tailSize - 1].y = newHead->y;
//
//}
//
//SDL_Rect keepMoving() {
//	SDL_Rect newTail;
//	newTail.h = 32;
//	newTail.w = 32;
//
//	switch (currentDirection) {
//		case Direction::UP:
//			newTail.x = Snake[tailSize - 1].x;
//			newTail.y = Snake[tailSize - 1].y - 32;
//			break;
//
//		case Direction::DOWN:
//			newTail.x = Snake[tailSize - 1].x;
//			newTail.y = Snake[tailSize - 1].y + 32;
//			break;
//
//		case Direction::LEFT:
//			newTail.x = Snake[tailSize - 1].x - 32;
//			newTail.y = Snake[tailSize - 1].y;
//			break;
//
//		case Direction::RIGHT:
//			newTail.x = Snake[tailSize - 1].x + 32;
//			newTail.y = Snake[tailSize - 1].y;
//			break;
//
//		default:
//			break;
//	}
//
//	return newTail;
//}
//
//void printSnake() {
//	for (int i = 0; i < tailSize; i++) {
//		cout <<  i << ": " << Snake[i].x << ", " << Snake[i].y << endl;
//	}
//}