#include "TextObject.h"

TextObject::TextObject(SDL_Rect rect, const char* font_file, const char* _text, SDL_Color text_color)
{
	textRect = rect;
	textColor = text_color;
	text = _text;
	fontFile = font_file;

	initText();	
}

bool TextObject::initText()
{
	if (TTF_Init() < 0)
	{
		printf("Unable to initialize !SDL2_TTF! TTF Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		font = TTF_OpenFont(fontFile, 20);
		if (font == NULL)
		{
			printf("Unable to load font %s! TTF Error: %s\n", fontFile, TTF_GetError());
			return false;
		}
		else
		{
			textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

			if (textSurface == NULL)
			{
				printf("Unable to load font texture %s! TTF Error: %s\n", fontFile, TTF_GetError());
				return false;
			}
		}

	}

	return true;
}

void TextObject::setText(string newText)
{
	text = newText;
	initText();
}

void TextObject::setFont(const char* newFont)
{
	if (TTF_Init() >= 0)
	{
		font = TTF_OpenFont(fontFile, 14);
	}
	
}

void TextObject::setTextColor(SDL_Color newColor)
{
}

void TextObject::setRect(SDL_Rect rect)
{
}



SDL_Surface* TextObject::getSurface()
{
	return textSurface;
}

SDL_Rect* TextObject::getRect()
{
	return &textRect;
}

const char* TextObject::getText()
{
	return text.c_str();
}

TextObject::~TextObject()
{
	SDL_FreeSurface(textSurface);
}