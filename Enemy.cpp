#pragma once
#include "Enemy.hpp"

Enemy::Enemy() {
	type = 1;
	reload = 20;
	fire = 0;
	RGBTimer = 0;
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
int Enemy::getType() {
	return type;
}
void Enemy::setType(int type) {
	this->type = type;
}

int Enemy::getRGBTimer() {
	return this->RGBTimer;
}
void Enemy::setRGBTimer(int time) {
	this->RGBTimer = time;
}
