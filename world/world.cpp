#include "world.h"
#include "game_object.h"
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

bool World::collides(const Vec<float>& position) const {
    int x = std::floor(position.x);
    int y = std::floor(position.y);
    return tilemap(x,y) == Tile::Platform;
}

GameObject* World::create_player() {
    player = std::make_unique<GameObject>(Vec<float>{10, 5}, Vec<float>{1,1}, *this);
    return player.get();
}

void World::move_to(Vec<float>& position, const Vec<float>& size, Vec<float>& velocity) {
    // test for collisions on the bottom or top first
    if (collides(position) && collides({position.x+size.x, position.y})) {
        position.y = ceil(position.y);
        velocity.y = 0;
    } else if (collides({position.x, position.y+size.y}) && collides({position.x+size.x, position.y+size.y})){
        position.y = floor(position.y);
        velocity.y = 0;
    }
    // then test for collisions on the left and right sides
    if (collides(position) && collides({position.x, position.y+size.y})) {
        position.x = ceil(position.x);
        velocity.x = 0;
    } else if (collides({position.x+size.x, position.y}) && collides({position.x+size.x, position.y+size.y})){
        position.x = floor(position.x);
        velocity.x = 0;
    }
    // now test each corner
    if (collides(position)) { //bottom left corner
        float dx = ceil(position.x) - position.x;
        float dy = ceil(position.y) - position.y;

        if (dx > dy) {
            position.y = ceil(position.y);
            velocity.y = 0;
        } else {
            position.x = ceil(position.x);
            velocity.x = 0;
        }
    } else if (collides({position.x+size.x, position.y})) { //bottom right corner
        float dx = position.x - floor(position.x);
        float dy = ceil(position.y) - position.y;

        if (dx > dy) {
            position.y = ceil(position.y);
            velocity.y = 0;
        } else {
            position.x = floor(position.x);
            velocity.x = 0;
        }
    } else if (collides({position.x, position.y+size.y})) { //top left corner
        float dx = ceil(position.x) - position.x;
        float dy = position.y - floor(position.y);

        if (dx > dy) {
            position.y = floor(position.y);
            velocity.y = 0;
        } else {
            position.x = ceil(position.x);
            velocity.x = 0;
        }
    } else if (collides({position.x+size.x, position.y+size.y})) { //top right corner
        float dx =  position.x - floor(position.x);
        float dy =  position.y - floor(position.y);

        if (dx > dy) {
            position.y = floor(position.y);
            velocity.y = 0;
        } else {
            position.x = floor(position.x);
            velocity.x = 0;
        }
    }
}

void World::update(float dt) {
    // //currently only player
    // auto position = player->position;
    // auto velocity = player->velocity;
    // auto acceleration = player->acceleration;
    //
    // velocity += 0.5f * acceleration * dt;
    // position += velocity*dt;
    // velocity += 0.5f * acceleration * dt; //calculate half the velocity before position calculation and half after
    // velocity.x *= damping;
    //
    // velocity.x = std::clamp(velocity.x, -terminal_velocity, terminal_velocity);
    // velocity.y = std::clamp(velocity.y, -terminal_velocity, terminal_velocity);
    //
    // //check for collisions x
    // Vec<float> future{position.x, player->position.y};
    // if (collides(future)) {
    //     player->velocity.x = 0;
    //     player->acceleration.x = 0;
    // } else {
    //     player->velocity.x = velocity.x;
    //     player->position.x = position.x;
    //     player->acceleration.x = acceleration.x;
    // }
    //
    // //y collisions
    // future.x = player->position.x;
    // future.y = position.y;
    // if (collides(future)) {
    //     player->velocity.y = 0;
    //     player->acceleration.y = gravity;
    // } else {
    //     player->position.y = position.y;
    //     player->velocity.y = velocity.y;
    //     player->acceleration.y = acceleration.y;
    // }

    // ... the code to update velocity and position
    auto position = player->position;
    auto velocity = player->velocity;
    auto acceleration = player->acceleration;

    velocity += 0.5f * acceleration * dt;
    position += velocity*dt;
    velocity += 0.5f * acceleration * dt; //calculate half the velocity before position calculation and half after
    velocity.x *= physics.damping;

    velocity.x = std::clamp(velocity.x, -physics.terminal_velocity, physics.terminal_velocity);
    velocity.y = std::clamp(velocity.y, -physics.terminal_velocity, physics.terminal_velocity);

    // check for collisions in the world - x direction
    Vec<float> future_position{position.x, player->position.y};
    Vec<float> future_velocity{velocity.x, 0};
    move_to(future_position, player->size, future_velocity);
    // now y direction after (maybe) moving in x
    future_velocity.y = velocity.y;
    future_position.y = position.y;
    move_to(future_position, player->size, future_velocity);
    // update the player position and velocity
    player->position = future_position;
    player->velocity = future_velocity;

}
