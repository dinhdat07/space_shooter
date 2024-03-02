
#include "Game.hpp"

void Game::start() {
	initGame();
	initPlayer();
	atexit(SDL_Quit);
	while (true) {
		prepareScene();
		//scrollBackground();
		getInput();
		presentEntities();
		presentScene();
	}
	return;
}

// First step: Init SDL and background
// Documents: lazyfoo, parallelrealities
void Game::initGame() {

	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Couldn't initialize SDL: \n" << SDL_GetError();
		exit(1);
	}

	//create window
	app.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!app.window) {
		std::cout << "Cannot open " << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << " window\n"
			<< SDL_GetError();
		exit(1);
	}

	//create renderer
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (!app.renderer) {
		std::cout << "Failed to create renderer: \n" << SDL_GetError();
		exit(1);
	}

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	//init PNG/JPG loading	 
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		std::cout << "Could not initialize SDL Image : " << SDL_GetError() << "\n";
		exit(-1);
	}

}


void Game::initPlayer() {
	player = Player();
	player.setX(100);
	player.setY(100);
	player.setTexture(loadTexture("gfx/player.png"));
}


void Game::presentEntities() {
	//if player still alive (update later)
	player.move();

	if (player.Fire() && player.getReload() == 0) {
		bullet = Entity();
		bullet.setTexture(loadTexture("gfx/playerBullet.png"));
		int w, h;
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &w, &h);
		bullet.setX(player.getX() + h/2);
		bullet.setY(player.getY() + w/2);
		bullet.setDX(PLAYER_BULLET_SPEED);
		bullet.setHealth(1);
		Bullets.push_back(bullet);
		player.setReload(8);
	}

	draw(player.getTexture(), player.getX(), player.getY());

	//Checking removable bullets
	for (int i = 0; i < Bullets.size(); ++i) {
		Entity& b = Bullets[i];
		b.move();
		draw(b.getTexture(), b.getX(), b.getY());

		if (b.getX() > SCREEN_WIDTH) {
			Bullets.erase(Bullets.begin() + i);
			--i; // Adjust the index after erasing
		}
	}
}


void Game::getInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYUP:
			player.keyUp(&event.key);
			break;
		case SDL_KEYDOWN:
			player.keyDown(&event.key);
			break;
		}
	}
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);
}

void Game::presentScene() {

	if (player.getReload() > 0) {
		player.setReload(player.getReload() - 1);
	}

	SDL_RenderPresent(app.renderer);
	SDL_Delay(16);
}

/*void Game::scrollBackground() {
	int w, h;
	app.background = loadTexture("gfx/background.png");
	SDL_QueryTexture(app.background, NULL, NULL, &w, &h);
	if (--backgroundX < -SCREEN_WIDTH)
	{
		backgroundX = 0;
	}
	drawBackground(app.background, backgroundX);
	drawBackground(app.background, backgroundX + w);

}


void Game::drawBackground(SDL_Texture* texture, int x) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_RenderCopy(app.renderer, texture, NULL, &stretchRect);
}*/



SDL_Texture* Game::loadTexture(std::string path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(app.renderer, path.c_str());
	return texture;
}

void Game::draw(SDL_Texture* texture, int x, int y) {
	SDL_Rect target;
	target.x = x;
	target.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &target);
}


