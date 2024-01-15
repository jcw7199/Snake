#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Snake.h"
using namespace std;


int main(int argc, char* args[]) {

	GameWindow win = GameWindow("Hello World", "images/map.bmp");
    SDL_Surface* surf = SDL_LoadBMP("images/map.bmp");
    
    SDL_Rect rect = SDL_Rect { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, surf->w, surf->h };


    GameObject map = GameObject(rect, "images/map.bmp");
    win.init();
    win.loadObject(map);
    
    

    win.eventHandler();
    win.deleteWindow();
    
    //Start up SDL and create window
    //images/map.bmp
    
    //win.eventHandler();
	return 0;
}