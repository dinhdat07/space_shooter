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
		bool playing;
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

	std::vector<Entity> powerUps;
	Entity powerup;

	//sound and music
	Mix_Chunk* explosionSound = NULL;
	Mix_Chunk* bulletSound = NULL;
	Mix_Chunk* buttonSound =  NULL;
	Mix_Music* music = NULL;

	//font
	TTF_Font* font = NULL;
	TTF_Font* titleFont = NULL;

	int gameCount;
	int score, highScore;
	std::stringstream scoreText, hScoreText, LPText;


	void initGame();
	void titleScreen();
	void initPlayer();
	void presentEntities();
	void getInput();
	void HUD();
	void presentScene();
	void draw(SDL_Texture*, int, int);
	void drawRect(SDL_Texture*, SDL_Rect*, int, int);
	void drawBackground();
	void addExplosion(int, int, int);
	void addPowerUp(int, int, int);
	SDL_Texture* loadTexture(std::string);
	bool detectCollision(int, int, int, int, int, int, int, int);
	void endScreen();
public:
	void start();
};