#include <core/snake_engine.h>

namespace snake_game {

    SnakeEngine::SnakeEngine(size_t board_size) : board_size_(board_size) {
        snake_ = Snake();
        game_state_ = kCont;

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

        if (game_state_ == kOver) {
            ci::gl::drawStringCentered(
                    "Game Over",
                    glm::vec2(100, 100),
                    ci::Color("white"), ci::Font("Helvetica", 24));

            ci::gl::drawStringCentered(
                    "Press R to restart!",
                    glm::vec2(100, 300),
                    ci::Color("white"), ci::Font("Helvetica", 24));

            return;
        }

        // set tile types to snake for tiles on board where snake exists
        for (vec2 position: snake_.body_) {
            size_t x_spot = (int) position.x;
            size_t y_spot = (int) position.y;
            board_[x_spot][y_spot].type_ = Tile::SNAKE;
        }

        float tile_size = (float) board_window_size / board_size_;
        for (size_t i = 0; i < board_size_; i++) {
            for (size_t j = 0; j < board_size_; j++) {
                Tile tile = board_[i][j];
                ci::gl::color(tile.color_);

                vec2 box_top_corner = board_window_corner + vec2(tile_size * i, tile_size * j);
                vec2 box_bottom_corner = box_top_corner + vec2(tile_size, tile_size);
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
        if (game_state_ == kOver) {
            return;
        }

        CheckWallCollision();

        switch (snake_.direction_) {
            case Snake::kUp:
                MoveUp();
                break;
            case Snake::kDown:
                MoveDown();
                break;
            case Snake::kLeft:
                MoveLeft();
                break;
            case Snake::kRight:
                MoveRight();
                break;
        }
    }

    void SnakeEngine::TurnSnake(Snake::Direction new_direction) {
        if (snake_.body_.size() > 1) {
            Snake::Direction current_direction = snake_.direction_;
            if (current_direction == Snake::kUp && new_direction == Snake::kDown) {
                game_state_ = kOver;
                return;
            }
            if (current_direction == Snake::kDown && new_direction == Snake::kUp) {
                game_state_ = kOver;
                return;
            }
            if (current_direction == Snake::kLeft && new_direction == Snake::kRight) {
                game_state_ = kOver;
                return;
            }
            if (current_direction == Snake::kRight && new_direction == Snake::kLeft) {
                game_state_ = kOver;
                return;
            }
        }
        snake_.direction_ = new_direction;
    }

    void SnakeEngine::MoveUp() {
        UpdateBoardLeavingTile();
        snake_.MoveUp();
    }

    void SnakeEngine::MoveDown() {
        UpdateBoardLeavingTile();
        snake_.MoveDown();
    }

    void SnakeEngine::MoveLeft() {
        UpdateBoardLeavingTile();
        snake_.MoveLeft();
    }

    void SnakeEngine::MoveRight() {
        UpdateBoardLeavingTile();
        snake_.MoveRight();
    }

    void SnakeEngine::UpdateBoardLeavingTile() {
        vec2 last_position = snake_.body_.back();
        size_t x_spot = (size_t) last_position.x;
        size_t y_spot = (size_t) last_position.y;
        board_[x_spot][y_spot].type_ = Tile::EMPTY;
    }

    void SnakeEngine::CheckWallCollision() {
        vec2 next_position = GetNextSnakeHeadPosition(snake_.direction_);
        if (next_position.x < 0 || next_position.x > board_size_) {
            game_state_ = kOver;
        }

        if (next_position.y < 0 || next_position.y > board_size_) {
            game_state_ = kOver;
        }
    }

    const vec2 SnakeEngine::GetNextSnakeHeadPosition(Snake::Direction direction) const {
        return snake_.GetNextHeadPosition(direction);
    }
}