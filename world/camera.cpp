//
// Created by Louis Tennier on 2/4/26.
//

#include "camera.h"
#include "graphics.h"
#include "physics.h"

Camera::Camera(Graphics& graphics, float tilesize)
    : graphics{graphics}, tilesize{tilesize} {
    calculate_visible_tiles();
}

void Camera::calculate_visible_tiles() {
    Vec<int> num_tiles = Vec{graphics.width, graphics.height} /(2* static_cast<int>(tilesize))+Vec{1,1};
    Vec<int> center{static_cast<int>(location.x), static_cast<int>(location.y)};
    visible_max = center + num_tiles;
    visible_min = center - num_tiles;
}

Vec<float> Camera::world_to_screen(const Vec<float>& world_position) const {
    Vec<float> pixel = (world_position - location) * static_cast<float>(tilesize);

    pixel += Vec<float>{graphics.width/2.0f, graphics.height/2.0f};

    pixel.y = graphics.height - pixel.y;

    return pixel;
}
