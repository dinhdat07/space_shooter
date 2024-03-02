#pragma once
#include "common.h"

#include "Entity.hpp"
#include "Player.hpp"


class Game {
private:
    struct {
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Texture* background;
    } app;

    int backgroundX;
    Player player;

    Entity bullet;

    std::vector<Entity> Bullets;

    void initGame();
    void initPlayer();
    void getInput();
    void prepareScene();
    void presentEntities();
    void presentScene();
    
    //void scrollBackground();
    //void drawBackground(SDL_Texture*, int);

    SDL_Texture* loadTexture(std::string);
    void draw(SDL_Texture*, int, int);

public: 
    void start();
};