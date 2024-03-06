#pragma once
#include <SDl.h>

class Entity {
protected:
	int x, y,health;
	double dx, dy;
	SDL_Texture* texture;
	int side;
public:
	Entity();
	void move();
	void setX(int);
	void setY(int);
	void setDX(double);
	void setDY(double);
	void setHealth(int);
	void setTexture(SDL_Texture*);
	void setSide(int);

	int getX();
	int getY();
	double getDX();
	double getDY();
	int getHealth();
	int	Side();
	SDL_Texture* getTexture();
	virtual ~Entity();
};