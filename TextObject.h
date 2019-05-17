#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction.h"
enum {RED_TEXT, WHITE_TEXT, BLACK_TEXT};

class TextObject 

{
public:
	TextObject();
	~TextObject();
	void SetText(const std::string& text, TTF_Font* Font, SDL_Renderer* screen);
	void SetColor(const int& r, const int& g, const int& b);
	void SetColor(int type );
	void Render(SDL_Renderer* gRenderer);
	void SetRect(const int&x, const int& y) { Rect.x = x; Rect.y = y; }
	SDL_Rect GetRect() { return Rect; }

private:
	SDL_Rect Rect;
	SDL_Texture* textTexture;
	SDL_Color text_color_;
};

#endif;