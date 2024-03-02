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

int Entity::getHealth() {
	return health;
}

void Entity::setY(int y) {
	this->y = y;
}

void Entity::setDX(int dx) {
	this->dx = dx;
}

void Entity::setDY(int dy) {
	this->dy = dy;
}

void Entity::setTexture(SDL_Texture* texture) {
	this->texture = texture;
}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}

int Entity::getDX() {
	return dx;
}

int Entity::getDY() {
	return dy;
}

SDL_Texture* Entity::getTexture() {
	return texture;
}

Entity::~Entity() {

}