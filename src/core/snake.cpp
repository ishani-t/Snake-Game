#include <core/snake.h>

namespace snake_game {

    Snake::Snake() {
        body_.push_back(vec2(10, 100));
        body_.push_back(vec2(10, 100 + kGridSize));
        body_.push_back(vec2(10, 100 + kGridSize + kGridSize));
    }

    void Snake::MoveUp() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(0, -20);

        direction_ = UP;
    }

    void Snake::MoveDown() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(0, 20);

        direction_ = DOWN;
    }

    void Snake::MoveLeft() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(-20, 0);

        direction_ = LEFT;
    }

    void Snake::MoveRight() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(20, 0);

        direction_ = RIGHT;
    }

}