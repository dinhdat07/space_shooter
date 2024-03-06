#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <time.h>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int PLAYER_SPEED = 4;
const int PLAYER_BULLET_SPEED = 16;

const int ENEMY_SPEED = -4;
const int ENEMY_BULLET_SPEED = 8;

const int MAX_KEYBOARD_KEYS = 350;

