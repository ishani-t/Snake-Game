#pragma once

#include "cinder/gl/gl.h"

namespace snake_game {
    class Tile {
    public:
        enum TileType { SNAKE, FOOD, EMPTY};
        TileType type_;
        ci::Color color_;

        Tile();

    private:
    };
}
