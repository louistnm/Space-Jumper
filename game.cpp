//
// Created by Louis Tennier on 1/28/26.
//

#include "game.h"

Game::Game(std::string title, int width, int height)
    : graphics{title, width, height}, dt{1.0/60.0}, lag{0.0},
performance_frequency{SDL_GetPerformanceFrequency()},
prev_counter{SDL_GetPerformanceCounter()} { //constructing private data in initializer list

    //load the first "level"
    //boundary walls
    world.add_platform(0,0,30,1);
    world.add_platform(0,0,1,10);
    world.add_platform(30,0,1,10);
    world.add_platform(0,10,31,1);

    //platforms
    world.add_platform(3,7,4,1);
    world.add_platform(13,4,6,1);

    player = world.create_player();
}

void Game::input() {
    player->handle_input();
}

void Game::update() {
    Uint64 now = SDL_GetPerformanceCounter();
    lag += (now - prev_counter) / (float)performance_frequency; //casting C style cause SDL is C
    prev_counter = now;
    while (lag >= dt) {
        world.update(dt);
        lag -= dt; //accumulate lag enough so that you update world every 60th of a second
    }
    ;}

void Game::render() {
    //clear
    graphics.clear();

    //draw world
    for(auto &platform : world.get_platforms()) {
        graphics.draw(platform, {0, 255, 0, 255});
    }
    auto [player_sprite, color] = player->get_sprite();
    graphics.draw(player_sprite, color);

    //update()
    graphics.update();
}
