#include <core/snake_engine.h>

namespace snake_game {

    SnakeEngine::SnakeEngine() {
        snake_ = Snake();
    }

    void SnakeEngine::Draw() {

        // Draw snake in green
        ci::gl::color(ci::Color("green"));
        for (vec2 box_position: snake_.body_) {
            cinder::Rectf rect = ci::Rectf(box_position, box_position + vec2(kGridSize, kGridSize));
            ci::gl::drawSolidRect(rect);
        }

    }

    void SnakeEngine::Update() {

    }

    void SnakeEngine::MoveUp() {
        snake_.MoveUp();
    }

    void SnakeEngine::MoveDown() {
        snake_.MoveDown();
    }

    void SnakeEngine::MoveLeft() {
        snake_.MoveLeft();
    }

    void SnakeEngine::MoveRight() {
        snake_.MoveRight();
    }
}