#include "Game.hpp"
using namespace std;

void Game::start() {
	initGame();
	initPlayer();
	while (true) {
		prepareScene();
		//drawBackground();
		getInput();
		presentEntities();
		presentScene();
	}
}



void Game::initGame() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(-1);
	}
	app.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!app.window) {
		cout << "Could not create window : " << SDL_GetError() << endl;
		exit(-1);
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (!app.renderer) {
		cout << "Could not create renderer : " << SDL_GetError() << endl;
		exit(-1);
	}
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		cout << "Could not initialize SDL Image : " << SDL_GetError() << endl;
		exit(-1);
	}

	backgroundX = 0;

	enemySpawnTimer = 60;

	player.setTexture(loadTexture("gfx/player.png"));

	playerBullet.setDX(PLAYER_BULLET_SPEED);
	playerBullet.setHealth(1);
	playerBullet.setTexture(loadTexture("gfx/playerBullet.png"));

}

void Game::initPlayer() {
	player.setX(SCREEN_WIDTH / 2);
	player.setY(SCREEN_HEIGHT / 2 - 50);
	player.setHealth(1);
	player.resetInput();
}

void Game::getInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYUP:
			player.keyUp(&e.key);
			break;
		case SDL_KEYDOWN:
			player.keyDown(&e.key);
			break;
		}
	}
}

void Game::presentEntities() {
	player.move();
	draw(player.getTexture(), player.getX(), player.getY()); //Draw player plane

	int wP, hP;
	if (player.Fire() == true && player.getReload() == 0) {
		playerBullet.setTexture(loadTexture("gfx/playerBullet.png"));
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
		playerBullet.setX(player.getX() + wP/2);
		playerBullet.setY(player.getY() + hP/2);
		playerBullet.setDX(PLAYER_BULLET_SPEED);
		player.setReload(5);
		Bullets.push_back(playerBullet);
	}

	//Spawn enemy
	if (enemySpawnTimer == 0) {
		enemy = new Enemy();
		enemy->setX(SCREEN_WIDTH - 80);
		enemy->setDX(ENEMY_SPEED);
		enemy->setTexture(loadTexture("gfx/enemy.png"));
		enemy->setHealth(1);
		enemySpawnTimer = 60;
		enemy->setY(rand() % 400 + 100);
		Enemies.push_back(enemy);
	}

	//Checking removable fighter
	for (auto i = Enemies.begin(); i != Enemies.end(); ) {
		int w, h;
		SDL_QueryTexture((*i)->getTexture(), NULL, NULL, &w, &h);
		if ((*i)->getX() <= -w) {
			i = Enemies.erase(i);
		}
		else {
			if ((*i)->getReload() > 0) (*i)->setReload((*i)->getReload() - 1);
			else {
				enemyBullet.setTexture(loadTexture("gfx/alienBullet.png"));
				enemyBullet.setX((*i)->getX() - w/2);
				enemyBullet.setY((*i)->getY() + h/2);
				float dx = player.getX() - enemyBullet.getX();
				float dy = player.getY() - enemyBullet.getY();
				float distance = sqrt(dx * dx + dy * dy);
				dx /= distance;
				dy /= distance;
				enemyBullet.setDX(dx * ENEMY_BULLET_SPEED);
				enemyBullet.setDY(dy * ENEMY_BULLET_SPEED);
				(*i)->setReload(60);
				Bullets.push_back(enemyBullet);
			}
			(*i)->move();
			draw((*i)->getTexture(), (*i)->getX(), (*i)->getY());
			i++;
		}
	}

	//Checking removable bullets
	for (auto i = Bullets.begin(); i != Bullets.end(); ) {
		if (i->getX() < 0 || i->getX() > SCREEN_WIDTH || i->getY() < 0 || i->getY() > SCREEN_HEIGHT) {
			i = Bullets.erase(i);
		}
		else {
			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i++;
		}
	}
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void Game::presentScene() {
	if (enemySpawnTimer > 0) {
		enemySpawnTimer--;
	}
	if (player.getReload() > 0) {
		player.setReload(player.getReload() - 1);
	}
	SDL_RenderPresent(app.renderer);
	SDL_Delay(16);
}

SDL_Texture* Game::loadTexture(std::string path) {
	SDL_Texture* texture = IMG_LoadTexture(app.renderer, path.c_str());
	if (texture == NULL) {
		cout << "Error loading image : " << IMG_GetError() << endl;
		exit(-1);
	}
	return texture;
}

void Game::draw(SDL_Texture* texture, int x, int y) {
	SDL_Rect target;
	target.x = x;
	target.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &target);
}

bool Game::detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}
