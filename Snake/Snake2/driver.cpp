#include <iostream>
#include "Snake.h"
using namespace std;

int main(int argc, char* args[]) {
	cout << "main()\n";
	// start the game
    Snake newSnake = Snake();
	newSnake.start(); 
	//cout << "Hello world\n";
	//system("pause");
	return 0;
}
