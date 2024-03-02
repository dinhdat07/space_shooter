#pragma once
#include "Entity.hpp"

class Player:public Entity {
private:
	bool up, down, left, right, fire;
	int reload;
public:
	Player();
	void move(); //overriding
	void keyDown(SDL_KeyboardEvent*);
	void keyUp(SDL_KeyboardEvent*);
	bool Fire();
	int getReload();
	void setReload(int);
};
