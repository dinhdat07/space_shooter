#pragma once
#include "Entity.hpp"

class Player:public Entity {
private:
	bool up, down, left, right, fire;
	int reload;
	int enhance;
public:
	Player();
	void move();
	void setEnhance(int enhance);
	int getEnhance();
	void keyDown(SDL_KeyboardEvent*);
	void keyUp(SDL_KeyboardEvent*);
	bool Fire();
	int getReload();
	void setReload(int);
	void resetInput();
};
