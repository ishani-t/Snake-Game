#pragma once

#include <core/snake.h>
#include <core/tile.h>
#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/audio/audio.h"

namespace snake_game {

    const vec2 board_window_corner(100, 100);
    const size_t board_window_size = 600;

    const vec2 score_window_corner(750, 100);
    const vec2 score_window_size(150, 150);

    const vec2 control_window_corner(750, 300);
    const vec2 control_window_size(150, 400);

    class SnakeEngine {
    public:
        Snake snake_;

        enum State {kCont, kOver};
        State game_state_;

        std::vector<std::vector<Tile>> board_;

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

        /**
         * Setter for food tile position. Used for testing purposes
         * @param food vec2 representing food tile's position
         */
        void setFood(const vec2 &food);

    private:
        size_t board_size_;
        vec2 food_;
        ci::audio::VoiceRef eat_sound_;

        /**
         * Sets board tile to empty when snake leaves it.
         */
        void UpdateBoardLeavingTile();

        /**
         * Ends game if snake will collide with wall.
         */
        void CheckWallCollision();

        /**
         * Ends game if snake collides with itself.
         */
        void CheckSnakeCollision();

        /**
         * Determines if snake will eat food in next turn.
         */
        void CheckEatFood();

        /**
         * Determines what position the snake's head will be next based on given direction.
         * @return Position of the snake head on next turn for given direction.
         */
        vec2 GetNextSnakeHeadPosition(Snake::Direction direction) const;

        /**
         * Generates a random spot for a food tile (where there is no snake).
         */
        void GenerateRandomFoodTile();

        /**
         * Helper method to draw screen for game over.
         */
        void DrawGameOverScreen();

        /**
         * Sets the tile types on board depending on snake and food positions.
         */
        void SetTileTypes();

        /**
         * Draws tiles from board.
         */
        void DrawTiles();

        /**
         * Draws score display.
         */
         void DrawScore();

         /**
          * Draws controls menu
          */
          void DrawControls();

    };
}