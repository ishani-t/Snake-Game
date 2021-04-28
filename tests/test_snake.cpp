#include <catch2/catch.hpp>

#include <core/snake.h>

TEST_CASE("Move snake up") {

    SECTION("snake of size 1") {
        snake_game::Snake snake = snake_game::Snake(2, 2);
        snake.MoveUp();
        vec2 expectedPosition1(2, 1);
        REQUIRE(expectedPosition1 == snake.body_[0]);

        snake.MoveUp();
        vec2 expectedPosition2(2, 0);
        REQUIRE(expectedPosition2 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kUp == snake.direction_);
    }

    SECTION("snake of size 4") {
        snake_game::Snake snake = snake_game::Snake(2, 2); // block 1
        snake.body_.push_back(vec2(3, 2)); // block 2
        snake.body_.push_back(vec2(4, 2)); // block 3
        snake.body_.push_back(vec2(5, 2)); // block 4

        REQUIRE(snake.body_.size() == 4);

        snake.MoveUp();

        vec2 expectedBlock1Position(2, 1);
        vec2 expectedBlock2Position(2, 2);
        vec2 expectedBlock3Position(3, 2);
        vec2 expectedBlock4Position(4, 2);
        std::vector<vec2> expectedSnakeBody { expectedBlock1Position,
                                              expectedBlock2Position,
                                              expectedBlock3Position,
                                              expectedBlock4Position};

        REQUIRE(expectedSnakeBody == snake.body_);
        REQUIRE(snake_game::Snake::kUp == snake.direction_);
    }

}

TEST_CASE("Move snake down") {

    SECTION("snake of size 1") {
        snake_game::Snake snake = snake_game::Snake(2, 2);
        snake.MoveDown();
        vec2 expectedPosition1(2, 3);
        REQUIRE(expectedPosition1 == snake.body_[0]);

        snake.MoveDown();
        vec2 expectedPosition2(2, 4);
        REQUIRE(expectedPosition2 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kDown == snake.direction_);
    }

    SECTION("snake of size 4") {
        snake_game::Snake snake = snake_game::Snake(2, 2); // block 1
        snake.body_.push_back(vec2(3, 2)); // block 2
        snake.body_.push_back(vec2(4, 2)); // block 3
        snake.body_.push_back(vec2(5, 2)); // block 4

        snake.MoveDown();

        vec2 expectedBlock1Position(2, 3);
        vec2 expectedBlock2Position(2, 2);
        vec2 expectedBlock3Position(3, 2);
        vec2 expectedBlock4Position(4, 2);
        std::vector<vec2> expectedSnakeBody { expectedBlock1Position,
                                              expectedBlock2Position,
                                              expectedBlock3Position,
                                              expectedBlock4Position};

        REQUIRE(expectedSnakeBody == snake.body_);
        REQUIRE(snake_game::Snake::kDown == snake.direction_);
    }

}

TEST_CASE("Move snake left") {

    SECTION("snake of size 1") {
        snake_game::Snake snake = snake_game::Snake(2, 2);
        snake.MoveLeft();
        vec2 expectedPosition1(1, 2);
        REQUIRE(expectedPosition1 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kLeft == snake.direction_);

        snake.MoveLeft();
        vec2 expectedPosition2(0, 2);
        REQUIRE(expectedPosition2 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kLeft == snake.direction_);
    }

    SECTION("snake of size 4") {
        snake_game::Snake snake = snake_game::Snake(2, 2); // block 1
        snake.body_.push_back(vec2(2, 3)); // block 2
        snake.body_.push_back(vec2(2, 4)); // block 3
        snake.body_.push_back(vec2(2, 5)); // block 4

        snake.MoveLeft();

        vec2 expectedBlock1Position(1, 2);
        vec2 expectedBlock2Position(2, 2);
        vec2 expectedBlock3Position(2, 3);
        vec2 expectedBlock4Position(2, 4);
        std::vector<vec2> expectedSnakeBody { expectedBlock1Position,
                                              expectedBlock2Position,
                                              expectedBlock3Position,
                                              expectedBlock4Position};

        REQUIRE(expectedSnakeBody == snake.body_);
        REQUIRE(snake_game::Snake::kLeft == snake.direction_);
    }

}

TEST_CASE("Move snake right") {
    SECTION("snake of size 1") {
        snake_game::Snake snake = snake_game::Snake(2, 2);
        snake.MoveRight();
        vec2 expectedPosition1(3, 2);
        REQUIRE(expectedPosition1 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kRight == snake.direction_);

        snake.MoveRight();
        vec2 expectedPosition2(4, 2);
        REQUIRE(expectedPosition2 == snake.body_[0]);
        REQUIRE(snake_game::Snake::kRight == snake.direction_);
    }

    SECTION("snake of size 4") {
        snake_game::Snake snake = snake_game::Snake(2, 2); // block 1
        snake.body_.push_back(vec2(2, 3)); // block 2
        snake.body_.push_back(vec2(2, 4)); // block 3
        snake.body_.push_back(vec2(2, 5)); // block 4

        snake.MoveRight();

        vec2 expectedBlock1Position(3, 2);
        vec2 expectedBlock2Position(2, 2);
        vec2 expectedBlock3Position(2, 3);
        vec2 expectedBlock4Position(2, 4);
        std::vector<vec2> expectedSnakeBody { expectedBlock1Position,
                                              expectedBlock2Position,
                                              expectedBlock3Position,
                                              expectedBlock4Position};

        REQUIRE(expectedSnakeBody == snake.body_);
        REQUIRE(snake_game::Snake::kRight == snake.direction_);
    }
}

TEST_CASE("GetNextHeadPosition method") {
     snake_game::Snake snake = snake_game::Snake(2, 2);

    SECTION("up direction") {
        snake_game::Snake snake = snake_game::Snake(2, 2);
        vec2 actualPosition = snake.GetNextHeadPosition(snake_game::Snake::kUp);
        vec2 expectedPosition(2, 1);
        REQUIRE(actualPosition == expectedPosition);
    }

    SECTION("down direction") {
        vec2 actualPosition = snake.GetNextHeadPosition(snake_game::Snake::kDown);
        vec2 expectedPosition(2, 3);
        REQUIRE(actualPosition == expectedPosition);
    }

    SECTION("left direction") {
        vec2 actualPosition = snake.GetNextHeadPosition(snake_game::Snake::kLeft);
        vec2 expectedPosition(1, 2);
        REQUIRE(actualPosition == expectedPosition);
    }

    SECTION("right direction") {
        vec2 actualPosition = snake.GetNextHeadPosition(snake_game::Snake::kRight);
        vec2 expectedPosition(3, 2);
        REQUIRE(actualPosition == expectedPosition);
    }
}

TEST_CASE("Add Size (snake eating)") {
    snake_game::Snake snake = snake_game::Snake(2, 2);

    snake.AddSize();
    REQUIRE(snake.body_.size() == 2);
    REQUIRE(snake.body_[1] == vec2(2, 2));

    snake.AddSize();
    REQUIRE(snake.body_.size() == 3);
    REQUIRE(snake.body_[2] == vec2(2, 2));
}
