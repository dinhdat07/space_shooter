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
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int PLAYER_SPEED = 8;
const int PLAYER_BULLET_SPEED = 24;

const int ENEMY_SPEED = -8;
const int ENEMY_BULLET_SPEED = 12;

const int MAX_KEYBOARD_KEYS = 350;

