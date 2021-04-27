#pragma once

#include <core/snake.h>
#include <core/tile.h>
#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

namespace snake_game {

    class SnakeEngine {
    public:
        Snake snake_;

        /**
         * Empty constructor for SnakeEngine object.
         */
        SnakeEngine(size_t board_size = 20);

        /**
         * Draws each rectangle to form the snake on the board.
         */
        void Draw();

        /**
         * Moves the snake in its current direction.
         */
        void Update();

        /**
         * Moves snake up one spot on the grid.
         */
        void MoveUp();

        /**
         * Moves snake down one spot on the grid.
         */
        void MoveDown();

        /**
         * Moves snake left one spot on the grid.
         */
        void MoveLeft();

        /**
         * Moves snake right one spot on the grid.
         */
        void MoveRight();

    private:
        std::vector<std::vector<Tile>> board_;
    };
}