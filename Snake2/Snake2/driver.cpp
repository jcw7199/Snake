#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Snake.h"
using namespace std;


int main(int argc, char* args[]) {
	
	Snake newSnake = Snake();

	newSnake.start();
    
	return 0;
}