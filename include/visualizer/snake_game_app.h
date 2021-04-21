#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace snake_game {

    class SnakeGameApp : public ci::app::App {
    public:
        SnakeGameApp();

        void draw() override;
        void keyDown(ci::app::KeyEvent event) override;

        const double kWindowSize = 875;
        const double kMargin = 100;
        const size_t kImageDimension = 28;

    private:
        double size_;
    };

}
