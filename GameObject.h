#pragma once
#include<iostream>
#include<SDL.h>
#include <SDL_image.h>

using namespace std; 

enum class MOVEMENT_TYPE { STATIC, DYNAMIC, CONSTANT };
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };
class GameObject
{
private:
	const char* textureFile;
	SDL_Rect* objectRect;
	MOVEMENT_TYPE objectMVMT;
	Direction objectDir;
	static int total;
	int ID;
	
public:
	GameObject(SDL_Rect* rect = nullptr, const char* file = nullptr,
			   MOVEMENT_TYPE mt = MOVEMENT_TYPE::STATIC, Direction dir = Direction::NONE);

	GameObject(const GameObject& other);
	
	void setTexture(const char* textureFile);
	void setRect(SDL_Rect rect);
	void setDir(Direction dir) { objectDir = dir; }
	void setMVMT(MOVEMENT_TYPE mt) { objectMVMT = mt; }
	
	const char* getTextureFile() { return textureFile; }
	Direction getDir() { return objectDir; }
	MOVEMENT_TYPE getMVMT() { return objectMVMT; }
	int getID() { return ID; }
	SDL_Rect getRect();

	GameObject operator=(GameObject& other);
	void destroyObject();
	~GameObject();
};

