#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <core/snake_engine.h>

namespace snake_game {

    const double kWindowSize = 950;

    class SnakeGameApp : public ci::app::App {
    public:
        SnakeGameApp();

        void setup() override;
        void draw() override;
        void update() override;
        void keyDown(ci::app::KeyEvent event) override;

        const double kWindowSize = snake_game::kWindowSize;
        const double kMargin = 100;

    private:
        SnakeEngine snake_engine_;
        bool is_paused_;
    };

}