#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <vector>
#include "tilemap.h"
#include "vec.h"
#include "game_object.h"

class World {
public:
    World(int width, int height);

    void add_platform(float x, float y, float width, float height);
    bool collides(const Vec<float>& position) const;
    GameObject* create_player();
    void move_to(Vec<float>& position, const Vec<float>& size, Vec<float>& velocity);
    void update(float dt);

    Tilemap tilemap;
    Physics physics;

private:
    std::unique_ptr<GameObject> player;

};