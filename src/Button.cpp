#include"Button.hpp"

Button::Button() {
	x = y = h = w = 0;
	hovered = false;
	texture = NULL;
}

void Button::setX(int x) {
	this->x = x;
}
void Button::setY(int y) {
	this->y = y;
}
void Button::setW(int w) {
	this->w = w;
}

void Button::setH(int h) {
	this->h = h;
}
void Button::setHovered(bool hovered) {
	this->hovered = hovered;
}

void Button::setTexture(SDL_Texture* texture) {
	this->texture = texture;
}

int Button::getX() {
	return x;
}
int Button::getY() {
	return y;
}
int Button::getW() {
	return w;
}
int Button::getH() {
	return h;
}
bool Button::isHovered() {
	return hovered;
}
SDL_Texture* Button::getTexture() {
	return texture;
}