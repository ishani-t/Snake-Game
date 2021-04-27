#include <core/snake_engine.h>

namespace snake_game {

    SnakeEngine::SnakeEngine(size_t board_size) {
        snake_ = Snake();

        for (size_t i = 0; i < board_size; i++) {
            std::vector<Tile> row;
            for (size_t j = 0; j < board_size; j++) {
                Tile tile = Tile();
                row.push_back(tile);
            }
            board_.push_back(row);
            row.clear();
        }

    }

    void SnakeEngine::Draw() {

        for (vec2 position: snake_.body_) {
            size_t x_spot = (int) position.x;
            size_t y_spot = (int) position.y;
            board_[x_spot][y_spot].type_ = Tile::SNAKE;
        }

        for (size_t i = 0; i < board_[0].size(); i++) {
            for (size_t j = 0; j < board_[1]. size(); j++) {
                Tile tile = board_[i][j];
                ci::gl::color(tile.color_);

                vec2 box_top_corner = vec2(100 + 20*i, 100 + 20*j);
                vec2 box_bottom_corner = box_top_corner + vec2(20, 20);
                cinder::Rectf rect = ci::Rectf(box_top_corner, box_bottom_corner);

                if (tile.type_ == Tile::EMPTY) {
                    ci::gl::drawStrokedRect(rect);
                } else {
                    ci::gl::drawSolidRect(rect);
                }
            }
        }

    }

    void SnakeEngine::Update() {
        switch (snake_.direction_) {
            case Snake::UP:
                MoveUp();
                break;
            case Snake::DOWN:
                MoveDown();
                break;
            case Snake::LEFT:
                MoveLeft();
                break;
            case Snake::RIGHT:
                MoveRight();
                break;
        }
    }

    void SnakeEngine::MoveUp() {
        vec2 last_position = snake_.body_.back();
        size_t x_spot = (size_t) last_position.x;
        size_t y_spot = (size_t) last_position.y;
        board_[x_spot][y_spot].type_ = Tile::EMPTY;

        snake_.MoveUp();
    }

    void SnakeEngine::MoveDown() {
        vec2 last_position = snake_.body_.back();
        size_t x_spot = (size_t) last_position.x;
        size_t y_spot = (size_t) last_position.y;
        board_[x_spot][y_spot].type_ = Tile::EMPTY;

        snake_.MoveDown();
    }

    void SnakeEngine::MoveLeft() {
        vec2 last_position = snake_.body_.back();
        size_t x_spot = (size_t) last_position.x;
        size_t y_spot = (size_t) last_position.y;
        board_[x_spot][y_spot].type_ = Tile::EMPTY;

        snake_.MoveLeft();
    }

    void SnakeEngine::MoveRight() {
        vec2 last_position = snake_.body_.back();
        size_t x_spot = (size_t) last_position.x;
        size_t y_spot = (size_t) last_position.y;
        board_[x_spot][y_spot].type_ = Tile::EMPTY;

        snake_.MoveRight();
    }
}