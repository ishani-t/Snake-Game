#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

namespace snake_game {
    const int kGridSize = 20;


    class Snake {
    public:

        // body stores a vector of positions
        std::vector<vec2> body_;

        enum Direction { UP, DOWN, LEFT, RIGHT };
        Direction direction_;

        Snake();

        void MoveUp();

        void MoveDown();

        void MoveLeft();

        void MoveRight();

    private:
    };

}
