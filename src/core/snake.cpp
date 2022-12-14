#include <core/snake.h>

namespace snake_game {

    Snake::Snake(size_t x, size_t y) {
        body_.push_back(vec2(x, y));
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

    vec2 Snake::GetNextHeadPosition(Snake::Direction direction) const {
        vec2 next_position = body_.front();
        switch (direction) {
            case Snake::kUp:
                next_position += vec2(0, -1);
                break;
            case Snake::kDown:
                next_position += vec2(0, 1);
                break;
            case Snake::kLeft:
                next_position += vec2(-1, 0);
                break;
            case Snake::kRight:
                next_position += vec2(1, 0);
                break;
        }
        return next_position;
    }

    void Snake::AddSize() {
        vec2 last_position = body_.back();
        body_.push_back(last_position);
    }

}