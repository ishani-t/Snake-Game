#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

namespace snake_game {

    class Snake {
    public:
        std::vector<vec2> body_;

        enum Direction { kUp, kDown, kLeft, kRight };
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

        /**
         * Determines the next position of the snake's head.
         * @param direction specified for snake to travel in
         * @return vec2 representing next position
         */
        vec2 GetNextHeadPosition(Direction direction) const;

    private:
    };

}