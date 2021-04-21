#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

namespace snake_game {
    const int kGridSize = 20;

    class Snake {
    public:
        // body stores a vector of positions
        std::vector<vec2> body_;

        enum Direction { UP, DOWN, LEFT, RIGHT };
        Direction direction_;

        /**
         * Empty constructor for snake object.
         */
        Snake();

        /**
         * Moves the snake up by one block on the grid.
         */
        void MoveUp();

        /**
         * Moves the snake down by one block on the grid.
         */
        void MoveDown();

        /**
         * Moves the snake left by one block on the grid.
         */
        void MoveLeft();

        /**
         * Moves the snake right by one block on the grid.
         */
        void MoveRight();

    private:
    };

}