#include <visualizer/snake_game_app.h>

namespace snake_game {

    SnakeGameApp::SnakeGameApp() {
        ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
    }

    void SnakeGameApp::draw() {
        ci::Color8u background_color(250, 250, 250);
        ci::gl::clear(background_color);

        ci::gl::drawStringCentered(
                "TEST TEST TEST TEST",
                glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

    }

    void SnakeGameApp::keyDown(ci::app::KeyEvent event) {
//        AppBase::keyDown(event);
    }
}


