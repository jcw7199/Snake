#include "TextObject.h"

TextObject::TextObject(SDL_Rect rect, const char* font_file, const char* _text, SDL_Color text_color)
{
	cout << "TextObject::TextObject()\n";

	textRect = rect;
	textColor = text_color;
	text = _text;
	fontFile = font_file;

	initText();	
}

bool TextObject::initText()
{
	cout << "TextObject::initText()\n";

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
	cout << "TextObject::setText()\n";

	text = newText;
	initText();
}

void TextObject::setFont(const char* newFont)
{
	cout << "TextObject::setFont()\n";

	if (TTF_Init() >= 0)
	{
		font = TTF_OpenFont(fontFile, 14);
	}
	
}

void TextObject::setTextColor(SDL_Color newColor)
{
	cout << "TextObject::setTextColor()\n";

}

void TextObject::setRect(SDL_Rect rect)
{
	cout << "TextObject::setRect()\n";

}



SDL_Surface* TextObject::getSurface()
{
	cout << "TextObject::getSurface()\n";

	return textSurface;
}

SDL_Rect* TextObject::getRect()
{
	cout << "TextObject::getRect()\n";

	return &textRect;
}

const char* TextObject::getText()
{
	cout << "TextObject::getText()\n";

	return text.c_str();
}

TextObject::~TextObject()
{
	cout << "TextObject::~TextObject()\n";

	SDL_FreeSurface(textSurface);
	TTF_Quit();
}