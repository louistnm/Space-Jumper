#include "world.h"
#include "player.h"
#include "physics.h"
#include <SDL3/SDL_rect.h>
#include <algorithm>

World::World(int width, int height)
    : tilemap{width,height} {}

void World::add_platform(float x, float y, float width, float height) {
    for (int i{0}; i < height; ++i) {
        for (int j{0}; j < width; ++j) {
            tilemap(x+j, y+i) = Tile::Platform;
        }
    }
}

bool World::collides(const Vec<float> position) {
    int x = std::floor(position.x);
    int y = std::floor(position.y);
    return tilemap(x,y) == Tile::Platform;
} //[&] gives access to the scope's variables

Player* World::create_player() {
    player = std::make_unique<Player>(Vec<float>{10, 5}, Vec<float>{64,64});
    return player.get();
}

void World::update(float dt) {
    //currently only player
    auto position = player->position;
    auto velocity = player->velocity;
    auto acceleration = player->acceleration;

    velocity += 0.5f * acceleration * dt;
    position += velocity*dt;
    velocity += 0.5f * acceleration * dt; //calculate half the velocity before position calculation and half after
    velocity.x *= damping;

    velocity.x = std::clamp(velocity.x, -terminal_velocity, terminal_velocity);
    velocity.y = std::clamp(velocity.y, -terminal_velocity, terminal_velocity);

    //check for collisions x
    Vec<float> future{position.x, player->position.y};
    if (collides(future)) {
        player->velocity.x = 0;
        player->acceleration.x = 0;
    } else {
        player->velocity.x = velocity.x;
        player->position.x = position.x;
        player->acceleration.x = acceleration.x;
    }
    //y collisions
    future.x = player->position.x;
    future.y = position.y;
    if (collides(future)) {
        player->velocity.y = 0;
        player->acceleration.y = gravity;
    } else {
        player->velocity.y = velocity.y;
        player->acceleration.y = acceleration.y;
        player->position.y = position.y;
    }
}
