#pragma once
#include<iostream>
#include<SDL.h>
#include <SDL_image.h>

using namespace std; 

enum class MOVEMENT_TYPE { STATIC, DYNAMIC, CONSTANT };
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT};
class GameObject
{
private:
	const char* textureFile;
	SDL_Rect objectRect;
	MOVEMENT_TYPE objectMVMT;
	
public:
	SDL_Surface* objectSurface;
	GameObject();
	GameObject(SDL_Rect rect, const char* file,
			   MOVEMENT_TYPE mt = MOVEMENT_TYPE::STATIC);

	GameObject operator=(GameObject other);

	void moveObject(SDL_Rect rect) { objectRect = rect; }
	
	const char* getTextureFile() { return textureFile; }
	MOVEMENT_TYPE getMVMT() { return objectMVMT; }
	SDL_Rect* getRect();
	
	void printRect();
	void setTexture(const char* textureFile);
	void setRect(SDL_Rect rect);
	void setMVMT(MOVEMENT_TYPE mt) { objectMVMT = mt; }
	void destroyObject();
	~GameObject();
};

