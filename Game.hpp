#pragma once
#include "common.h"

#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game {
private:
	struct {
		SDL_Renderer* renderer;
		SDL_Window* window;
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
	//int score, highScore;
	void initGame();
	void initPlayer();
	void presentEntities();
	void getInput();
	void presentScene();
	void draw(SDL_Texture*, int, int);
	SDL_Texture* loadTexture(std::string);
	bool detectCollision(int, int, int, int, int, int, int, int);
public:
	void start();
};