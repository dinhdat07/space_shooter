#pragma once
#include <SDl.h>

class Entity {
protected:
	int x, y, dx, dy, health;
	SDL_Texture* texture;
public:
	Entity();
	void move();
	void setX(int);
	void setY(int);
	void setDX(int);
	void setDY(int);
	void setHealth(int);
	void setTexture(SDL_Texture*);
	int getX();
	int getY();
	int getDX();
	int getDY();
	int getHealth();
	SDL_Texture* getTexture();
	virtual ~Entity();
};