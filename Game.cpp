#include "Game.hpp"
using namespace std;

void Game::start() {
	initGame();
	while (true) {
		if (!playAgain) {
			titleScreen();
		}
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
		draw(tSTXT, SCREEN_WIDTH/4, 100);
		draw(tShTXT, SCREEN_WIDTH/4 + 100, 200);
		draw(pressTXT, SCREEN_WIDTH / 4 + 75, 300);
		for (int i = 0; i < 3; i++) {
			draw(menuButton[i].getTexture(), menuButton[i].getX(), menuButton[i].getY());
		}
		presentScene();

		int x, y;
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
				if (e.key.keysym.scancode == SDL_SCANCODE_M) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;

			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 3; i++) {
					if (x >= menuButton[i].getX() && x <= menuButton[i].getX() + menuButton[i].getW() 
					&& y >= menuButton[i].getY() && y <= menuButton[i].getY() + menuButton[i].getH()) {
						if (!menuButton[i].isHovered()) {
							menuButton[i].setHovered(true);
							if (i == 0) menuButton[i].setTexture(loadTexture("gfx/startHoverButton.png"));
							if (i == 1) menuButton[i].setTexture(loadTexture("gfx/guideHoverButton.png"));
							if (i == 2) menuButton[i].setTexture(loadTexture("gfx/exitHoverButton.png"));
						}
					} else if (menuButton[i].isHovered()) {
						menuButton[i].setHovered(false);
						if (i == 0) menuButton[i].setTexture(loadTexture("gfx/startButton.png"));
						if (i == 1) menuButton[i].setTexture(loadTexture("gfx/guideButton.png"));
						if (i == 2) menuButton[i].setTexture(loadTexture("gfx/exitButton.png"));
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 3; ++i) {
					if (x >= menuButton[i].getX() && x <= menuButton[i].getX() + menuButton[i].getW()) {
						if (y >= menuButton[i].getY() && y <= menuButton[i].getY() + menuButton[i].getH()) {
							Mix_PlayChannel(-1, buttonSound, 0);
							if (i == 0) {
								app.playing = true;
								initPlayer();
								return;
							}
							else if (i == 1) {
								Guide();
							}
							else {
								exit(0);
							}
						}
					}
				}
				break;
			}
		}
	}
}


void Game::Guide() {
	SDL_Event e;
	backButton.setY(600);
	backButton.setX(450);
	backButton.setTexture(loadTexture("gfx/backButton.png"));
	int w, h;
	SDL_QueryTexture(backButton.getTexture(), NULL, NULL, &w, &h);
	backButton.setW(w);
	backButton.setH(h);

	SDL_Texture* guide = loadTexture("gfx/guide.png");

	int x, y;
	while (true) {
		drawBackground();
		draw(backButton.getTexture(), backButton.getX(), backButton.getY());
		draw(guide, 0, 25);
		presentScene();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_M) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
				&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					if (!backButton.isHovered()) {
						backButton.setHovered(true);
						backButton.setTexture(loadTexture("gfx/backHoverButton.png"));
					}
				} else if (backButton.isHovered()) {
					backButton.setHovered(false);
					backButton.setTexture(loadTexture("gfx/backButton.png"));
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				if (x >= backButton.getX() && x <= backButton.getX() + backButton.getW()
				&& y >= backButton.getY() && y <= backButton.getY() + backButton.getH()) {
					Mix_PlayChannel(-1, buttonSound, 0);
					return;
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
	string congrat = "Congrat. You achieve new high score!";

	SDL_Surface* endSf = TTF_RenderText_Solid(titleFont, gameover.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* endTXT = SDL_CreateTextureFromSurface(app.renderer, endSf);

	SDL_Surface* scoreSf = TTF_RenderText_Solid(font, endScore.c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSf);

	SDL_Surface* congratSf = TTF_RenderText_Solid(font, congrat.c_str(), { 232, 46, 46, 0 });
	SDL_Texture* congratTXT = SDL_CreateTextureFromSurface(app.renderer, congratSf);

	if (surpass) {
		ofstream fout("scores.txt");
		fout << highScore << endl;
		fout.close();
	}

	while (true) {
		drawBackground();
		draw(endTXT, SCREEN_WIDTH / 4, 200);
		draw(scoreTXT, SCREEN_WIDTH / 4 + 225, 350);
		if (surpass) {
			draw(congratTXT, SCREEN_WIDTH / 4 + 100, 400);
		}

		for (int i = 0; i < 2; i++) {
			draw(endButton[i].getTexture(), endButton[i].getX(), endButton[i].getY());
		}
		presentScene();

		int x, y;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					exit(0);
					break;

				case SDL_KEYDOWN:
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
						enemySpawnTimer = 60;
						surpass = 0;
						score = 0;
						playAgain = true;
						app.playing = true;
						initPlayer();
						return;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						exit(0);
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_M) {
						if (Mix_PausedMusic()) {
							Mix_ResumeMusic();
						}
						else {
							Mix_PauseMusic();
						}
					}
					break;

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					for (int i = 0; i < 2; i++) {
						if (x >= endButton[i].getX() && x <= endButton[i].getX() + endButton[i].getW()
							&& y >= endButton[i].getY() && y <= endButton[i].getY() + endButton[i].getH()) {
							if (!endButton[i].isHovered()) {
								endButton[i].setHovered(true);
								if (i == 0) endButton[i].setTexture(loadTexture("gfx/menuHoverButton.png"));
								if (i == 1) endButton[i].setTexture(loadTexture("gfx/playHoverButton.png"));
							}
						}
						else if (endButton[i].isHovered()) {
							endButton[i].setHovered(false);
							if (i == 0) endButton[i].setTexture(loadTexture("gfx/menuButton.png"));
							if (i == 1) endButton[i].setTexture(loadTexture("gfx/playButton.png"));
						}
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x, &y);
					for (int i = 0; i < 2; i++) {
						if (x >= endButton[i].getX() && x <= endButton[i].getX() + endButton[i].getW()
							&& y >= endButton[i].getY() && y <= endButton[i].getY() + endButton[i].getH()) {
							    Mix_PlayChannel(-1, buttonSound, 0);
								enemySpawnTimer = 60;
								surpass = 0;
								score = 0;
								if (i == 0) {
									playAgain = false;
								} else {
									playAgain = true;
									app.playing = true;
									initPlayer();
								}
								return;
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
	playerExplosionSound = Mix_LoadWAV("sound/explosionSound.wav");
	buttonSound = Mix_LoadWAV("sound/buttonSound.mp3");
	bulletSound = Mix_LoadWAV("sound/bulletSound.ogg");
	powerupSound = Mix_LoadWAV("sound/earnPowerUp.ogg");

	explosionTexture = loadTexture("gfx/explosion.png");
	font = TTF_OpenFont("font/Goldeneye.ttf", 28);
	titleFont = TTF_OpenFont("font/Ghost.ttf", 90);
	Mix_PlayMusic(music, -1);

	//Button
	int w, h;
	menuButton[0].setTexture(loadTexture("gfx/startButton.png"));
	menuButton[1].setTexture(loadTexture("gfx/guideButton.png"));
	menuButton[2].setTexture(loadTexture("gfx/exitButton.png"));
	for (int i = 0; i < 3; i++) {
		menuButton[i].setX(475);
		menuButton[i].setY(SCREEN_WIDTH / 4 + 25);
		SDL_QueryTexture(menuButton[i].getTexture(), NULL, NULL, &w, &h);
		menuButton[i].setW(w);
		menuButton[i].setH(h);
		if (i) {
			menuButton[i].setY(menuButton[i - 1].getY() + menuButton[i - 1].getH() + 25);
		}
	}

	backButton.setY(600);
	backButton.setX(450);
	backButton.setTexture(loadTexture("gfx/backButton.png"));
	SDL_QueryTexture(backButton.getTexture(), NULL, NULL, &w, &h);
	backButton.setW(w);
	backButton.setH(h);

	endButton[0].setTexture(loadTexture("gfx/menuButton.png"));
	endButton[1].setTexture(loadTexture("gfx/playButton.png"));
	for (int i = 0; i < 2; i++) {
		endButton[i].setX(SCREEN_WIDTH / 4 + 25);
		endButton[i].setY(500);
		SDL_QueryTexture(endButton[i].getTexture(), NULL, NULL, &w, &h);
		endButton[i].setW(w);
		endButton[i].setH(h);
		if (i) {
			endButton[i].setX(endButton[i - 1].getX() + endButton[i - 1].getW() + 50);
		}
	}

	playAgain = false;

	pauseIcon = loadTexture("gfx/pauseIcon (2).png");
	SDL_Texture* guide = loadTexture("gfx/guide.png");

	enemySpawnTimer = 60;
	score = 0;

	ifstream fin("scores.txt");
	if (!fin.is_open()) {
		std::cout << "Can't open file scores.txt";
		exit(-1);
	}
	fin >> highScore;
	fin.close();
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
				Mix_PlayChannel(-1, buttonSound, 0);
				app.pause = !app.pause;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_M) {
				if (Mix_PausedMusic()) {
					Mix_ResumeMusic();
				} else {
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
		enemy->setHealth(5);
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
			if ( ((*i)->getY() < 0 && (*i)->getDY() < 0) || ((*i)->getY() > 640 && (*i)->getDY() > 0) ) {
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
			int wE, hE;
			SDL_QueryTexture((*j)->getTexture(), NULL, NULL, &wE, &hE);

			if (i->Type() && detectCollision(i->getX(), i->getY(), wB, hB, (*j)->getX(), (*j)->getY(), wE, hE)) {
				i->setHealth(0);
				(*j)->setHealth((*j)->getHealth() - 1);
				if (!(*j)->getHealth()) {
					int num = rand() % 10 + 1;
					if (num < 2) {
						addPowerUp((*j)->getX(), (*j)->getY(), 1);
					}
					else if (num < 3) {
						addPowerUp((*j)->getX(), (*j)->getY(), 2);
					}
				}
			}

			if (detectCollision(player.getX(), player.getY(), wP, hP, (*j)->getX(), (*j)->getY(), wE, hE)) {
				player.setHealth(0);
				addExplosion(player.getX(), player.getY(), 1);
				Mix_PlayChannel(-1, playerExplosionSound, 0);
				(*j)->setHealth(0);
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
					player.setHealth(player.getHealth() + 4);
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
	if (score > highScore) surpass = 1;
	highScore = max(highScore, score);
	scoreText << "Score : " << score;
	hScoreText << "High Score : " << highScore;
	LPText << "Life Points: " << player.getHealth();

	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);

	SDL_Surface* hsSurface = TTF_RenderText_Solid(font, hScoreText.str().c_str(), { 181, 13, 13, 0 });
	SDL_Texture* hsTXT = SDL_CreateTextureFromSurface(app.renderer, hsSurface);

	SDL_Surface* LPSurface = TTF_RenderText_Solid(font, LPText.str().c_str(), { 22, 184, 17, 0 });
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
