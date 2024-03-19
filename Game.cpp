#include "Game.hpp"
using namespace std;

void Game::start() {
	initGame();
	while (true) {
		titleScreen();
		while (app.playing) {
			prepareScene();
			drawBackground();

			if (player.getHealth()) {
				getInput();
			}

			if (!app.pause) {
				presentEntities();
				HUD();
			}
			else {
				Pause();
			}

			presentScene();
		}
		endScreen();
	}
}

void Game::titleScreen() {
	SDL_Event e;
	string title1 = "Space ", title2 = "Shooter";
	string instruct = "Press Space to protect the galaxy!";
	SDL_Surface* titleSpace = TTF_RenderText_Solid(titleFont, title1.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* tSTXT = SDL_CreateTextureFromSurface(app.renderer, titleSpace);

	SDL_Surface* titleShooter = TTF_RenderText_Solid(titleFont, title2.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* tShTXT = SDL_CreateTextureFromSurface(app.renderer, titleShooter);

	SDL_Surface* pressSf = TTF_RenderText_Solid(font, instruct.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* pressTXT = SDL_CreateTextureFromSurface(app.renderer, pressSf);
	while (true) {
		drawBackground();
		draw(tSTXT, SCREEN_WIDTH/4, 200);
		draw(tShTXT, SCREEN_WIDTH/4 + 100, 300);
		draw(pressTXT, SCREEN_WIDTH / 4 + 75, 400);
		presentScene();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					app.playing = true;
					initPlayer();
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					exit(0);
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_1) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			}
		}
	}
}

void Game::endScreen() {
	SDL_Event e;
	string gameover = "GAME OVER";
	string endScore = "Your score: " + to_string(score);
	string instruct = "Want to start over? Press Space";

	SDL_Surface* endSf = TTF_RenderText_Solid(titleFont, gameover.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* endTXT = SDL_CreateTextureFromSurface(app.renderer, endSf);

	SDL_Surface* scoreSf = TTF_RenderText_Solid(font, endScore.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSf);

	SDL_Surface* instructSf = TTF_RenderText_Solid(font, instruct.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* instructTXT = SDL_CreateTextureFromSurface(app.renderer, instructSf);
	while (true) {
		drawBackground();
		draw(endTXT, SCREEN_WIDTH / 4, 200);
		draw(scoreTXT, SCREEN_WIDTH / 4 + 225, 350);
		draw(instructTXT, SCREEN_WIDTH / 4 + 100, 400);
		presentScene();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					enemySpawnTimer = 60;
					score = 0;
					app.playing = true;
					initPlayer();
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					exit(0);
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_1) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			}
		}

	}
}

void Game::initGame() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		cout << "Could not initialize SDL Image : " << SDL_GetError() << endl;
		exit(-1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Could not initialize SDL Mixer : " << SDL_GetError() << endl;
		exit(-1);
	}

	if (TTF_Init() == -1) {
		cout << "Could not initialize SDL TTF : " << SDL_GetError() << endl;
		exit(-1);
	}

	Mix_AllocateChannels(8);

	backgroundX = 0;

	app.playing = false;
	app.background = loadTexture("gfx/background.png");

	player.setTexture(loadTexture("gfx/player.png"));
	playerBullet.setDX(PLAYER_BULLET_SPEED);
	playerBullet.setHealth(1);
	playerBullet.setTexture(loadTexture("gfx/playerBullet.png"));
	enemyBulletTexture = loadTexture("gfx/alienBullet.png");
	enemyTexture = loadTexture("gfx/enemy.png");

	music = Mix_LoadMUS("music/backgroundMusic.ogg");
	explosionSound = Mix_LoadWAV("sound/enemyExplosion.ogg");
	playerExplosionSound = Mix_LoadWAV("sound/explosionSound.ogg");
	buttonSound = Mix_LoadWAV("sound/buttonSound.ogg");
	bulletSound = Mix_LoadWAV("sound/bulletSound.ogg");
	powerupSound = Mix_LoadWAV("sound/earnPowerUp.ogg");

	explosionTexture = loadTexture("gfx/explosion.png");
	font = TTF_OpenFont("font/Goldeneye.ttf", 28);
	titleFont = TTF_OpenFont("font/Ghost.ttf", 90);
	Mix_PlayMusic(music, -1);

	pauseIcon = loadTexture("gfx/pauseIcon (2).png");
	if (pauseIcon == NULL) {
		std::cout << SDL_GetError();
		exit(-1);
	}

	enemySpawnTimer = 60;
	score = 0;
	highScore = 0;
}

void Game::initPlayer() {
	player.setX(SCREEN_WIDTH / 2);
	player.setY(SCREEN_HEIGHT / 2 - 50);
	player.setHealth(10);
	player.setEnhance(0);
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
			if (e.key.keysym.scancode == SDL_SCANCODE_P) {
				app.pause = !app.pause;
				if (Mix_PausedMusic()) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
			player.keyDown(&e.key);
			break;
		}
	}
}

void Game::Pause() {
	draw(pauseIcon, SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 2 - 225);
	string gamepause = "GAME PAUSED";
	SDL_Surface* pauseSf = TTF_RenderText_Solid(font, gamepause.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* pauseTXT = SDL_CreateTextureFromSurface(app.renderer, pauseSf);
	draw(pauseTXT, SCREEN_WIDTH / 2 - 100, 3 * SCREEN_HEIGHT / 4 - 50);
}

void Game::presentEntities() {
	if (player.getHealth() > 0) {
		player.move();
		draw(player.getTexture(), player.getX(), player.getY());
	}

	int wP, hP;
	if (player.Fire() == true && player.getReload() == 0) {
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
		playerBullet.setX(player.getX() + wP / 2);
		playerBullet.setY(player.getY() + hP / 2);
		playerBullet.setType(1);
		player.setReload(5);
		Bullets.push_back(playerBullet);
		if (player.getEnhance() > 0) {
			playerBullet.setX(player.getX());
			playerBullet.setY(player.getY());
			Bullets.push_back(playerBullet);

			playerBullet.setX(player.getX());
			playerBullet.setY(player.getY() + hP);
			Bullets.push_back(playerBullet);
		}
		Mix_PlayChannel(-1, bulletSound, 0);
	}

	//Spawn enemy
	if (enemySpawnTimer == 0) {
		enemy = new Enemy();
		enemy->setTexture(enemyTexture);
		int rate = rand() % 4;
		if (rate < 2) {
			enemy->setX(SCREEN_WIDTH - 80);
			enemy->setDX(ENEMY_SPEED - rand() % 8);
			enemy->setY(rand() % 400 + 100);
		}
		else {
			enemy->setX(SCREEN_WIDTH / 2 + rand() % 200);
			if (rate == 1) {
				enemy->setDY(-ENEMY_SPEED + rand() % 8);
				enemy->setY(-10);
			}
			else {
				enemy->setDY(ENEMY_SPEED - rand() % 8);
				enemy->setY(690);
			}
		}
		enemy->setHealth(1);
		enemySpawnTimer = 60;
		Enemies.push_back(enemy);
	}

	//Checking removable fighter
	for (auto i = Enemies.begin(); i != Enemies.end(); ) {
		int w, h;
		SDL_QueryTexture((*i)->getTexture(), NULL, NULL, &w, &h);
		if ((*i)->getX() <= -w) {
			i = Enemies.erase(i);
		}
		else if (!(*i)->getHealth()) {
			addExplosion((*i)->getX(), (*i)->getY(), 0);
			score++;
			Mix_PlayChannel(-1, explosionSound, 0);
			i = Enemies.erase(i);
		}
		else {
			if ((*i)->getReload() > 0) (*i)->setReload((*i)->getReload() - 1);
			else {
				enemyBullet.setTexture(enemyBulletTexture);
				enemyBullet.setX((*i)->getX() - w / 2);
				enemyBullet.setY((*i)->getY() + h / 2);
				float dx = player.getX() - enemyBullet.getX();
				float dy = player.getY() - enemyBullet.getY();
				float distance = sqrt(dx * dx + dy * dy);
				dx /= distance;
				dy /= distance;
				enemyBullet.setDX(dx * (ENEMY_BULLET_SPEED + rand() % 8));
				enemyBullet.setDY(dy * (ENEMY_BULLET_SPEED + rand() % 8));
				enemyBullet.setHealth(1);
				enemyBullet.setType(0);
				(*i)->setReload(30 + rand() % 30);
				Bullets.push_back(enemyBullet);
			}
			(*i)->move();
			if ( ((*i)->getY() < 0 && (*i)->getDY() < 0) || ((*i)->getY() > 680 && (*i)->getDY() > 0) ) {
				(*i)->setDY(-(*i)->getDY());
			}
			draw((*i)->getTexture(), (*i)->getX(), (*i)->getY());
			i++;
		}

	}

	//Checking removable bullets
	for (auto i = Bullets.begin(); i != Bullets.end(); ) {
		if (i->getX() < 0 || i->getX() > SCREEN_WIDTH || i->getY() < 0 || i->getY() > SCREEN_HEIGHT || !i->getHealth()) {
			i = Bullets.erase(i);
		}
		else {
			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i++;
		}
	}

	//Check bullet hit plane
	for (auto i = Bullets.begin(); i != Bullets.end(); i++) {
		int wB, hB, wP, hP;
		SDL_QueryTexture(i->getTexture(), NULL, NULL, &wB, &hB);
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
		if (!i->Type() && detectCollision(i->getX(), i->getY(), wB, hB, player.getX(), player.getY(), wP, hP)) {
			i->setHealth(0);
			player.setHealth(player.getHealth() - 2);
			if (player.getHealth() <= 0) {
				addExplosion(player.getX(), player.getY(), 1);
				Mix_PlayChannel(-1, playerExplosionSound, 0);
			}
		}
		for (auto j = Enemies.begin(); j != Enemies.end(); j++) {
			int wE, hE, wP, hP;
			SDL_QueryTexture((*j)->getTexture(), NULL, NULL, &wE, &hE);
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
			if (i->Type() && detectCollision(i->getX(), i->getY(), wB, hB, (*j)->getX(), (*j)->getY(), wE, hE)) {
				i->setHealth(0);
				(*j)->setHealth(0);
				int num = rand() % 10 + 1;
				if (num < 2) {
					addPowerUp((*j)->getX(), (*j)->getY(), 1);
				}
				else if (num < 3) {
					addPowerUp((*j)->getX(), (*j)->getY(), 2);
				}
			}
		}
	}

	//Draw explosion effect
	for (auto i = Explosion.begin(); i != Explosion.end(); ) {
		bool remove = false;
		for (auto j = i->begin(); j != i->end(); j++) {
			if (j->getA() <= 0) {
				remove = true;
				break;
			}
			SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
			SDL_SetTextureBlendMode(j->getTexture(), SDL_BLENDMODE_ADD);

			SDL_SetTextureColorMod(j->getTexture(), j->getR(), j->getG(), j->getB());
			SDL_SetTextureAlphaMod(j->getTexture(), j->getA());

			draw(j->getTexture(), j->getX(), j->getY());
			j->updateA(-15);

		}

		if (remove) {
			i = Explosion.erase(i);
		}
		else {
			i++;
		}
	}

	//do power ups
	for (auto i = powerUps.begin(); i != powerUps.end(); ) {
		if (i->getHealth() == 0 || i->getX() < 0 || i->getY() < 0 || i->getY() > 680) {
			i = powerUps.erase(i);
			break;
		} else {
			int wPU, hPU, wP, hP;
			SDL_QueryTexture(i->getTexture(), NULL, NULL, &wPU, &hPU);
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
			if (detectCollision(i->getX(), i->getY(), wPU, hPU, player.getX(), player.getY(), wP, hP)) {
				if (i->Type() == 1) {
					player.setHealth(player.getHealth() + 5);
				} else {
					player.setEnhance(300);
				}
				Mix_PlayChannel(-1, powerupSound, 0);
				i = powerUps.erase(i);
				break;
			}

			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i->setHealth(i->getHealth() - 1);
			i++;
		}
	}

}

void Game::HUD() {
	highScore = max(highScore, score);
	scoreText << "Score : " << score;
	hScoreText << "High Score : " << highScore;
	LPText << "Life Points: " << player.getHealth();

	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);

	SDL_Surface* hsSurface = TTF_RenderText_Solid(font, hScoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* hsTXT = SDL_CreateTextureFromSurface(app.renderer, hsSurface);

	SDL_Surface* LPSurface = TTF_RenderText_Solid(font, LPText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* LPTXT = SDL_CreateTextureFromSurface(app.renderer, LPSurface);

	draw(scoreTXT, 20, 20);
	draw(hsTXT, 20, 60);
	draw(LPTXT, 20, 100);
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void Game::addExplosion(int x, int y, int type) {
	explosion.setTexture(explosionTexture);
	explosion.setX(x + rand() % 32);
	explosion.setY(y + rand() % 32);
	explosion.setDX(0); explosion.setDY(0);
	explosion.setType(type);
	std::vector<Effect> tmp;
	for (int j = 0; j < 10; j++) {
		switch (rand() % 4) {
		case 0:
			explosion.setRGBA(255, 255, 0, 200); //YELLOW
			break;
		case 1:
			explosion.setRGBA(255, 0, 0, 200); //RED
			break;
		case 2:
			explosion.setRGBA(255, 128, 0, 200); //ORANGE
			break;
		case 3:
			explosion.setRGBA(255, 255, 255, 200); //WHITE
			break;
		}
		tmp.push_back(explosion);
	}
	Explosion.push_back(tmp);
}

void Game::addPowerUp(int x, int y, int type) {
	if(type == 1) powerup.setTexture(loadTexture("gfx/LP.png"));
	else if(type == 2) powerup.setTexture(loadTexture("gfx/enhanceATK.png"));
	powerup.setX(x + 20);
	powerup.setY(y + 20);
	powerup.setDX( -rand() % 5  - 1);
	powerup.setDY(rand() % 5 + 1);
	powerup.setHealth(150);
	powerup.setType(type);
	powerUps.push_back(powerup);
}


void Game::presentScene() {
	if (enemySpawnTimer > 0) {
		enemySpawnTimer--;
	}
	if (player.getReload() > 0) {
		player.setReload(player.getReload() - 1);
	}

	if (player.getEnhance() > 0) {
		player.setEnhance(player.getEnhance() - 1);
	}

	if (Explosion.empty() && player.getHealth() <= 0 && app.playing) {
		Bullets.clear();
		Enemies.clear();
		powerUps.clear();
		app.playing = false;
	}

	scoreText.str(std::string());
	hScoreText.str(std::string());
	LPText.str(std::string());
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

void Game::drawRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void Game::drawBackground() {
	int w, h;
	SDL_QueryTexture(app.background, NULL, NULL, &w, &h);
	if (-w > --backgroundX) {
		backgroundX = 0;
	}
	draw(app.background, backgroundX, 0);
	draw(app.background, backgroundX + w, 0);
}

bool Game::detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}
