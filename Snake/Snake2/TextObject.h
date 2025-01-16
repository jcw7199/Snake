#pragma once
#include "GameObject.h"
#include <SDL_ttf.h>
#include <string>

class TextObject
{
private:
	TTF_Font* font;
	SDL_Color textColor;
	string text;
	SDL_Surface* textSurface;
	const char* fontFile;
	SDL_Rect textRect;
public:
	TextObject(SDL_Rect rect = { 0, 0, 0, 0 }, const char* fontFile = nullptr, const char* _text = nullptr, SDL_Color text_color = { 0, 0, 0 });
	bool initText();
	void setText(string newText);
	void setFont(const char* newFont);
	void setTextColor(SDL_Color newColor = { 0, 0, 0 });
	void setRect(SDL_Rect rect);
	
	SDL_Surface* getSurface();
	SDL_Rect* getRect();
	const char* getText();
	~TextObject();
};

