#pragma once
#include<SDL.h>

class Button {
private:
	int x, y, w, h;
	bool hovered;
	SDL_Texture* texture;
public:
	Button();
	void setX(int);
	void setY(int);
	void setW(int);
	void setH(int);
	void setHovered(bool);
	void setTexture(SDL_Texture*);

	int getX();
	int getY();
	int getW();
	int getH();
	bool isHovered();
	SDL_Texture* getTexture();

};