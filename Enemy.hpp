#pragma once
#include "Entity.hpp"

class Enemy :public Entity {
private:
	int reload, fire;
public:
	Enemy();
	int getReload();
	void setReload(int);
	int enemyFire();
	void setFire(int);
};