//
// Created by Louis Tennier on 2/11/26.
//

#include "game_object.h"
#include "physics.h"

GameObject::GameObject(const Vec<float>& position, const Vec<float>& size, World& world)
    : position{position}, size{size} {
    acceleration = physics.gravity;
}

GameObject::~GameObject() {

}

void GameObject::input(World& world) {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    acceleration.x = 0;
    acceleration.y = physics.gravity;
    //velocity.x = velocity.y = 0;
    if (key_states[SDL_SCANCODE_A]) {
        //velocity.x += -16;
        acceleration.x -= physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_D]) {
        //velocity.x += 16;
        acceleration.x += physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_SPACE]) {
        velocity.y = physics.jump_velocity;
    }
}

void GameObject::update(World& world, double dt) {

}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {position, {255, 255, 255, 255}};
}
