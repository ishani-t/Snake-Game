#include <visualizer/snake_game_app.h>

namespace snake_game {

    SnakeGameApp::SnakeGameApp() {
        ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
        snake_engine_ = SnakeEngine();
    }

    void SnakeGameApp::draw() {
        ci::Color8u background_color(ci::Color("black"));
        ci::gl::clear(background_color);
        snake_engine_.Draw();
    }

    void SnakeGameApp::update() {
        snake_engine_.Update();
    }

    void SnakeGameApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_UP:
                snake_engine_.snake_.direction_ = Snake::UP;
                break;
            case ci::app::KeyEvent::KEY_DOWN:
                snake_engine_.snake_.direction_ = Snake::DOWN;
                break;
            case ci::app::KeyEvent::KEY_LEFT:
                snake_engine_.snake_.direction_ = Snake::LEFT;
                break;
            case ci::app::KeyEvent::KEY_RIGHT:
                snake_engine_.snake_.direction_ = Snake::RIGHT;
                break;
        }
    }
}