#pragma once

#include <core/snake.h>
#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

namespace snake_game {

    class SnakeEngine {
    public:
        SnakeEngine();

        void Draw();

        void Update();

        void MoveUp();

        void MoveDown();

        void MoveLeft();

        void MoveRight();

    private:
        Snake snake_;

    };


}
