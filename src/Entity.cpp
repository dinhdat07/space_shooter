#include "Entity.hpp"

Entity::Entity() {
	x = y = dx = dy = health = 0;
	texture = NULL;
}

void Entity::move() {
	this->x += dx;
	this->y += dy;
}

void Entity::setX(int x) {
	this->x = x;
}

void Entity::setHealth(int health) {
	this->health = health;
}

void Entity::setY(int y) {
	this->y = y;
}

void Entity::setDX(double dx) {
	this->dx = dx;
}

void Entity::setDY(double dy) {
	this->dy = dy;
}

void Entity::setTexture(SDL_Texture* texture) {
	this->texture = texture;
}

void Entity::setType(int type) {
	this->type = type;
}


int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}

double Entity::getDX() {
	return dx;
}

double Entity::getDY() {
	return dy;
}

SDL_Texture* Entity::getTexture() {
	return texture;
}

int Entity::getHealth() {
	return health;
}

int Entity::Type() {
	return type;
}

Entity::~Entity() {

}
