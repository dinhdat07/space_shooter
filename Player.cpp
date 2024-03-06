#include "common.h"
#include "Player.hpp"

Player::Player() {
	up = left = down = right = fire = reload = 0;
}

void Player::move() {
	if (up && left) {
		dy = -PLAYER_SPEED;
		dx = -PLAYER_SPEED;
	} else if (up && right) {
		dy = -PLAYER_SPEED;
		dx = PLAYER_SPEED;
	} else if (down && left) {
		dy = PLAYER_SPEED;
		dx = -PLAYER_SPEED;
	} else if (down && right) {
		dy = PLAYER_SPEED;
		dx = PLAYER_SPEED;
	} else if (up) {
		dy = -PLAYER_SPEED;
	} else if (down) {
		dy = PLAYER_SPEED;
	}
	else if (left) {
		dx = -PLAYER_SPEED;
	}
	else if (right) {
		dx = PLAYER_SPEED;
	}

	x = (x + dx < 0 ? 0 : (x + dx > 1240 ? 1240 : x + dx));
	y = (y + dy < 0 ? 0 : (y + dy > 680 ? 680 : y + dy));
	dx = dy = 0;
}

bool Player::Fire() {
	return fire;
}

int Player::getReload() {
	return reload;
}

void Player::setReload(int reload) {
	this->reload = reload;
}

void Player::keyDown(SDL_KeyboardEvent* event) {
	if (!(event->repeat)) {
		switch (event->keysym.scancode) {
		case SDL_SCANCODE_UP:
			up = true;
			break;
		case SDL_SCANCODE_DOWN:
			down = true;
			break;
		case SDL_SCANCODE_LEFT:
			left = true;
			break;
		case SDL_SCANCODE_RIGHT:
			right = true;
			break;
		case SDL_SCANCODE_LCTRL:
			fire = true;
			break;
		}
	}
}

void Player::keyUp(SDL_KeyboardEvent* event) {
	if (!(event->repeat)) {
		switch (event->keysym.scancode) {
		case SDL_SCANCODE_UP:
			up = false;
			break;
		case SDL_SCANCODE_DOWN:
			down = false;
			break;
		case SDL_SCANCODE_LEFT:
			left = false;
			break;
		case SDL_SCANCODE_RIGHT:
			right = false;
			break;
		case SDL_SCANCODE_LCTRL:
			fire = false;
			break;
		}
	}
}


void Player::resetInput() {
	left = up = right = down = fire = false;
}


