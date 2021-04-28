#include <catch2/catch.hpp>

#include <core/snake_engine.h>

TEST_CASE("Snake colliding with wall") {
    // initializes a 3x3 board with snake (singular tile) in center.
    snake_game::SnakeEngine snakeEngine(3);
    snakeEngine.snake_.body_[0] = vec2(1, 1);

    SECTION("top wall") {
        snakeEngine.snake_.direction_ = snake_game::Snake::kUp;
        snakeEngine.Update();
        snakeEngine.Update();
        REQUIRE(snakeEngine.game_state_ == snake_game::SnakeEngine::kOver);
    }

    SECTION("bottom wall") {
        snakeEngine.snake_.direction_ = snake_game::Snake::kDown;
        snakeEngine.Update();
        snakeEngine.Update();
        REQUIRE(snakeEngine.game_state_ == snake_game::SnakeEngine::kOver);
    }

    SECTION("left wall") {
        snakeEngine.snake_.direction_ = snake_game::Snake::kLeft;
        snakeEngine.Update();
        snakeEngine.Update();
        REQUIRE(snakeEngine.game_state_ == snake_game::SnakeEngine::kOver);
    }

    SECTION("right wall") {
        snakeEngine.snake_.direction_ = snake_game::Snake::kRight;
        snakeEngine.Update();
        snakeEngine.Update();
        REQUIRE(snakeEngine.game_state_ == snake_game::SnakeEngine::kOver);
    }

}

TEST_CASE("Snake colliding with itself") {
    snake_game::SnakeEngine snakeEngine(3);

    snakeEngine.snake_.body_[0] = vec2(1, 1);
    snakeEngine.snake_.body_.push_back(vec2(2, 1));
    snakeEngine.snake_.body_.push_back(vec2(2, 2));
    snakeEngine.snake_.body_.push_back(vec2(1, 2));

    snakeEngine.snake_.direction_ = snake_game::Snake::kDown;

    snakeEngine.Update();
    REQUIRE(snakeEngine.game_state_ == snake_game::SnakeEngine::kOver);
}

TEST_CASE("Snake eating food") {
    snake_game::SnakeEngine snakeEngine(3);
    snakeEngine.snake_.body_[0] = vec2(1, 1);

    snakeEngine.setFood(vec2(0, 0));

    snakeEngine.MoveLeft();
    snakeEngine.snake_.direction_ = snake_game::Snake::kUp;
    snakeEngine.Update();

    REQUIRE(snakeEngine.snake_.body_.size() == 2 );
    REQUIRE(snakeEngine.snake_.body_[0] == vec2(0, 0));
    REQUIRE(snakeEngine.snake_.body_[1] == vec2(0, 1));

}

TEST_CASE("Snake movement") {
    // initializes a 5x5 board with snake (singular tile) in center.
    snake_game::SnakeEngine snakeEngine(5);
    snakeEngine.snake_.body_[0] = vec2(2, 2);

    SECTION("MoveUp") {
        snakeEngine.MoveUp();
        REQUIRE(snakeEngine.board_[2][2].type_ == snake_game::Tile::EMPTY);
        REQUIRE(snakeEngine.board_[2][1].type_ == snake_game::Tile::EMPTY);
    }

    SECTION("MoveDown") {
        snakeEngine.MoveDown();
        REQUIRE(snakeEngine.board_[2][2].type_ == snake_game::Tile::EMPTY);
        REQUIRE(snakeEngine.board_[2][3].type_ == snake_game::Tile::EMPTY);
    }

    SECTION("MoveLeft") {
        snakeEngine.MoveLeft();
        REQUIRE(snakeEngine.board_[2][2].type_ == snake_game::Tile::EMPTY);
        REQUIRE(snakeEngine.board_[1][2].type_ == snake_game::Tile::EMPTY);
    }

    SECTION("MoveRight") {
        snakeEngine.MoveRight();
        REQUIRE(snakeEngine.board_[2][2].type_ == snake_game::Tile::EMPTY);
        REQUIRE(snakeEngine.board_[3][2].type_ == snake_game::Tile::EMPTY);
    }

    SECTION("TurnSnake") {
        snakeEngine.TurnSnake(snake_game::Snake::kUp);
        REQUIRE(snakeEngine.snake_.direction_ == snake_game::Snake::kUp);

        snakeEngine.TurnSnake(snake_game::Snake::kDown);
        REQUIRE(snakeEngine.snake_.direction_ == snake_game::Snake::kDown);

        snakeEngine.TurnSnake(snake_game::Snake::kLeft);
        REQUIRE(snakeEngine.snake_.direction_ == snake_game::Snake::kLeft);

        snakeEngine.TurnSnake(snake_game::Snake::kRight);
        REQUIRE(snakeEngine.snake_.direction_ == snake_game::Snake::kRight);
    }
}

