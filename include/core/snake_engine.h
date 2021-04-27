#pragma once

#include <core/snake.h>
#include <core/tile.h>
#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

namespace snake_game {

    const vec2 board_window_corner(100, 100);
    const size_t board_window_size = 500;

    class SnakeEngine {
    public:
        Snake snake_;

        enum State {kCont, kOver};
        State game_state_;


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
         * Updates the direction of snake when turning and checks for direction validity.
         * @param direction Direction (kUp, kDown, kLeft, kRight) to turn to
         */
        void TurnSnake(Snake::Direction new_direction);

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
        size_t board_size_;

        /**
         * Sets board tile to empty when snake leaves it.
         */
        void UpdateBoardLeavingTile();

        /**
         * Ends game if snake will collide with wall.
         */
        void CheckWallCollision();

        /**
         * Determines what position the snake's head will be next based on given direction.
         * @return Position of the snake head on next turn for given direction.
         */
        const vec2 GetNextSnakeHeadPosition(Snake::Direction direction) const;

    };
}