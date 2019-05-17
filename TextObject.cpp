#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject()
{
	Rect.x =0;
	Rect.y =0;
	Rect.w =0;
	Rect.h =0;
	textTexture = NULL;

	text_color_.r = 0;
	text_color_.g = 0;
	text_color_.b = 0;
}

TextObject::~TextObject()
{
	SDL_DestroyTexture(textTexture);
}

void TextObject::SetColor(const int & r, const int & g, const int & b)
{
	text_color_.r = r;
	text_color_.g = g;
	text_color_.b = b;
}
void TextObject::SetColor(int type )
{
	if ( type == RED_TEXT )
	{
		SDL_Color color = { 255, 0, 0};
		text_color_ = color;
	}
	else if (type == WHITE_TEXT )
	{
		SDL_Color color = { 255, 255, 255};
		text_color_ = color;
	}
	else if ( type == BLACK_TEXT)
	{
		SDL_Color color = { 0, 0, 0};
		text_color_ = color;
	}
}

void TextObject::Render(SDL_Renderer* gRenderer)
{
	SDL_RenderCopy(gRenderer, textTexture, NULL, &Rect);
}

void TextObject::SetText(const std::string & text, TTF_Font* Font, SDL_Renderer* screen)
{
	if (textTexture != NULL) {
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
	if (Font != NULL)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(Font, text.c_str(), text_color_);
		if (textSurface != NULL) {
			Rect.w = textSurface->w;
			Rect.h = textSurface->h;
			textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
			SDL_FreeSurface(textSurface);
			if (textSurface == NULL) {
			}
		}
	}
}