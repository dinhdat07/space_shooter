#pragma once
#include "Entity.hpp"

class Enemy :public Entity {
private:
	int reload, fire;
	int type;
	int RGBTimer;
public:
	Enemy();
	int getReload();
	void setReload(int);
	int enemyFire();
	void setFire(int);
	int getType();
	void setType(int);
	int getRGBTimer();
	void setRGBTimer(int);

};