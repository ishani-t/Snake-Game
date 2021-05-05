#include <visualizer/snake_game_app.h>

namespace snake_game {

    SnakeGameApp::SnakeGameApp() {
        ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
        snake_engine_ = SnakeEngine();
        is_paused_ = false;
    }

    void SnakeGameApp::setup() {
        return;
    }

    void SnakeGameApp::draw() {
        ci::Color8u background_color(ci::Color("black"));
        ci::gl::clear(background_color);
        snake_engine_.Draw();
    }

    void SnakeGameApp::update() {
        if (is_paused_) {
            return;
        }
        snake_engine_.Update();
    }

    void SnakeGameApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_UP:
                snake_engine_.TurnSnake(Snake::kUp);
                break;
            case ci::app::KeyEvent::KEY_DOWN:
                snake_engine_.TurnSnake(Snake::kDown);
                break;
            case ci::app::KeyEvent::KEY_LEFT:
                snake_engine_.TurnSnake(Snake ::kLeft);
                break;
            case ci::app::KeyEvent::KEY_RIGHT:
                snake_engine_.TurnSnake(Snake::kRight);
                break;
            case ci::app::KeyEvent::KEY_r:
                snake_engine_ = SnakeEngine();
                break;
            case ci::app::KeyEvent::KEY_q:
                std::exit(0);
            case ci::app::KeyEvent::KEY_p:
                is_paused_ = !is_paused_;
        }
    }
}