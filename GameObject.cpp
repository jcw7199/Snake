#include "GameObject.h"



GameObject::GameObject(SDL_Rect* rect, const char* file, MOVEMENT_TYPE mt, Direction dir) {
	cout << "GameObject::GameObject(): " << file << endl;
	if (file == nullptr) 
		cout << "	No file\n";
	total++;
	ID = total;
	objectRect = rect;
	objectMVMT = mt;
	textureFile = file;
	objectDir = dir;
	cout << "	Object created\n";
}

int GameObject::total = 0;
GameObject GameObject::operator=(GameObject& other) {
	cout << "GameObject::op=\n";
	if (this != &other) {
		this->destroyObject();
		GameObject o(&other.getRect(), other.getTextureFile(), other.getMVMT(), other.getDir());
	
		total++;
		ID = total;
	}
	
	return *this;
}

GameObject::GameObject(const GameObject& other) {
	cout << "GameObject::GameObject(GameObject& other) " << other.ID << other.textureFile;
	total++; 
	ID = total;
	objectRect = other.objectRect;
	objectMVMT = other.objectMVMT;
	textureFile = other.textureFile;
	objectDir = other.objectDir;
}

void GameObject::setTexture(const char* file){
	textureFile = file;
}

void GameObject::setRect(SDL_Rect rect) {
	//cout << "GameObject::setRect()\n";
	objectRect->x = rect.x;
	objectRect->y = rect.y;
	objectRect->h = rect.h;
	objectRect->w = rect.w;
}

SDL_Rect GameObject::getRect() {
	//cout << textureFile << " getRect()\n";
	if (objectRect != nullptr) {
		return *objectRect;
	}
	else {
		return { 0,0,0,0 };
	}
}

void GameObject::destroyObject() {
	cout << this->getID() << " GameObject::destroyObject()\n";
	total--;
	ID = NULL;
	textureFile = nullptr;
	objectRect = nullptr;
}

GameObject::~GameObject() {
	this->destroyObject();
}
