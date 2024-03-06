#pragma once
#include "Enemy.hpp"

Enemy::Enemy() {
	reload = 20;
	fire = 0;
}
int Enemy::getReload() {
	return reload;
}
void Enemy::setReload(int reload) {
	this->reload = reload;
}
int Enemy::enemyFire() {
	return fire;
}
void Enemy::setFire(int fire) {
	this->fire = fire;
}
