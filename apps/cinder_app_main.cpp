#include <visualizer/snake_game_app.h>

using snake_game::SnakeGameApp;

void prepareSettings(SnakeGameApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(SnakeGameApp, ci::app::RendererGl, prepareSettings);
