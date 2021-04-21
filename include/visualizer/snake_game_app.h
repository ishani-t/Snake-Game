#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <core/snake_engine.h>

namespace snake_game {

    class SnakeGameApp : public ci::app::App {
    public:
        SnakeGameApp();

        void draw() override;
        void update() override;
        void keyDown(ci::app::KeyEvent event) override;

        const double kWindowSize = 875;
        const double kMargin = 100;

    private:
        SnakeEngine snake_engine_;
    };

}