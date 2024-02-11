#include "GameObject.h"



GameObject::GameObject()
{
	objectRect = SDL_Rect{ 0, 0, 0, 0 };
	objectMVMT = MOVEMENT_TYPE::STATIC;
	textureFile = nullptr;
	objectSurface = nullptr;
}

GameObject::GameObject(SDL_Rect rect, const char* file, MOVEMENT_TYPE mt) {
	cout << "GameObject::GameObject(): " << file << endl;
	if (file == nullptr) 
		cout << "	No file\n";

	objectRect.x = rect.x;
	objectRect.y = rect.y;
	objectRect.w = rect.w;
	objectRect.h = rect.h;

	objectMVMT = mt;
	textureFile = file;

	objectSurface = SDL_LoadBMP(textureFile);
	
	cout << "	Object created\n";
}


GameObject GameObject::operator=(GameObject other) {
	cout << "GameObject::op=\n";

	if (this != &other && &other != nullptr) {		
		objectRect = other.objectRect;
		objectMVMT = other.objectMVMT;
		textureFile = other.textureFile;
		objectSurface = other.objectSurface;
	}

	return *this;
}


void GameObject::setTexture(const char* file){
	textureFile = file;
}

void GameObject::printRect()
{
	cout << "Rect: x = " << objectRect.x << ", y = " << objectRect.y
		<< ", w = " << objectRect.w << ", h = " << objectRect.h << endl;
}

void GameObject::setRect(SDL_Rect rect) {
	//cout << "GameObject::setRect()\n";
	objectRect = rect;
}

SDL_Rect* GameObject::getRect() {
	//cout << textureFile << " getRect()\n";	
	return &objectRect;
}

void GameObject::destroyObject() {
	//cout << " GameObject::destroyObject()\n";
	SDL_FreeSurface(objectSurface);
}

GameObject::~GameObject() {
	if (this != nullptr)
		this->destroyObject();
}
