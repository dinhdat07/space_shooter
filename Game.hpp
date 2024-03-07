#pragma once
#include "common.h"

#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Effect.hpp"

class Game {
private:
	struct {
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Texture* background;
	} app;

	Player player;
	Entity playerBullet;
	std::vector <Entity> Bullets;

	Enemy* enemy;
	Entity enemyBullet;
	int enemySpawnTimer;
	std::vector <Enemy*> Enemies;

	void prepareScene();
	int backgroundX;

	Effect explosion;
	std::vector <std::vector<Effect>> Explosion;

	//int score, highScore;
	void initGame();
	void initPlayer();
	void presentEntities();
	void getInput();
	void presentScene();
	void draw(SDL_Texture*, int, int);
	void drawRect(SDL_Texture*, SDL_Rect*, int, int);
	void drawBackground();
	void addExplosion(int, int);
	SDL_Texture* loadTexture(std::string);
	bool detectCollision(int, int, int, int, int, int, int, int);
public:
	void start();
};