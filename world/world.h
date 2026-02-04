#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <vector>
#include "tilemap.h"

class Player;
class World {
public:
    World(int width, int height);

    void add_platform(float x, float y, float width, float height);
    bool has_any_collisions(const SDL_FRect& box) const;
    Player* create_player();
    void update(float dt);

    Tilemap tilemap;

private:
    std::unique_ptr<Player> player;
};