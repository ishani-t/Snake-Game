#include <core/snake.h>

namespace snake_game {

    Snake::Snake() {
        body_.push_back(vec2(5, 5));
        body_.push_back(vec2(5, 6));
        body_.push_back(vec2(5, 7));
        body_.push_back(vec2(5, 8));
        body_.push_back(vec2(5, 9));
    }

    void Snake::MoveUp() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(0, -1);
        direction_ = kUp;
    }

    void Snake::MoveDown() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(0, 1);
        direction_ = kDown;
    }

    void Snake::MoveLeft() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(-1, 0);
        direction_ = kLeft;
    }

    void Snake::MoveRight() {
        for (size_t i = body_.size() - 1; i > 0 ; --i) {
            body_[i] = body_[i-1];
        }
        body_[0] += vec2(1, 0);
        direction_ = kRight;
    }

}