#include <core/snake_engine.h>
#include <visualizer/snake_game_app.h>

namespace snake_game {

    SnakeEngine::SnakeEngine(size_t board_size) : board_size_(board_size) {
        snake_ = Snake((size_t) board_size / 2, (size_t) board_size / 2);
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
        GenerateRandomFoodTile();

        ci::audio::SourceFileRef sourceFile1 = ci::audio::load( ci::app::loadAsset( "levelup.wav" ));
        eat_sound_ = ci::audio::Voice::create(sourceFile1);

        ci::audio::SourceFileRef sourceFile2 = ci::audio::load( ci::app::loadAsset( "losesound.mp3" ));
        lose_sound_ = ci::audio::Voice::create(sourceFile2);

    }

    void SnakeEngine::Draw() {

        if (game_state_ == kOver) {
            DrawGameOverScreen();
            return;
        }

        SetTileTypes();
        DrawTiles();
        DrawScore();
        DrawControls();
    }

    void SnakeEngine::Update() {
        if (game_state_ == kOver) {
            return;
        }

        CheckWallCollision();
        CheckSnakeCollision();

        switch (snake_.direction_) {
            case Snake::kUp:
                CheckEatFood();
                MoveUp();
                break;
            case Snake::kDown:
                CheckEatFood();
                MoveDown();
                break;
            case Snake::kLeft:
                CheckEatFood();
                MoveLeft();
                break;
            case Snake::kRight:
                CheckEatFood();
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
        if (next_position.x < 0 || next_position.x >= board_size_) {
            game_state_ = kOver;
            lose_sound_->start();
        }

        if (next_position.y < 0 || next_position.y >= board_size_) {
            game_state_ = kOver;
            lose_sound_->start();
        }
    }

    void SnakeEngine::CheckSnakeCollision() {
        vec2 next_position = GetNextSnakeHeadPosition(snake_.direction_);

        for (vec2 position: snake_.body_) {
            if (next_position == position && next_position != snake_.body_[0]) {
                game_state_ = kOver;
                lose_sound_->start();
            }
        }

    }

    void SnakeEngine::CheckEatFood() {
        vec2 next_position = GetNextSnakeHeadPosition(snake_.direction_);
        if (next_position == food_) {
            snake_.AddSize();

            size_t x_spot = (size_t) food_.x;
            size_t y_spot = (size_t) food_.y;
            board_[x_spot][y_spot].type_ = Tile::EMPTY;
            board_[x_spot][y_spot].color_ = ci::Color("green");
            GenerateRandomFoodTile();
            eat_sound_->start();
        }
    }

    vec2 SnakeEngine::GetNextSnakeHeadPosition(Snake::Direction direction) const {
        return snake_.GetNextHeadPosition(direction);
    }

    void SnakeEngine::GenerateRandomFoodTile() {
        vec2 food_spot = vec2(-1, -1);
        bool isValidParticle = false;
        while (!isValidParticle) {
            food_spot = vec2(cinder::randInt(0, board_size_ - 1), cinder::randInt(0, board_size_ - 1));
            size_t count = 0;

            if (GetNextSnakeHeadPosition(snake_.direction_) == food_spot) {
                count++;
            }

            for (vec2 position: snake_.body_) {
                if (position == food_spot) {
                    count++;
                    break;
                }
            }

            if (count == 0) {
                isValidParticle = true;
            }
        }

        food_ = food_spot;
    }

    void SnakeEngine::setFood(const vec2 &food) {
        food_ = food;
    }

    void SnakeEngine::DrawGameOverScreen() {
        ci::gl::drawStringCentered(
                "Game Over",
                glm::vec2(snake_game::kWindowSize / 2, snake_game::kWindowSize / 4),
                ci::Color("white"),
                ci::Font("Helvetica", 60));

        ci::gl::drawStringCentered(
               "Your score was " + std::to_string(snake_.body_.size()),
               glm::vec2(snake_game::kWindowSize / 2, snake_game::kWindowSize / 2),
               ci::Color("white"),
               ci::Font("Helvetica", 60));

        ci::gl::drawStringCentered(
                "Press R to restart!",
                glm::vec2(snake_game::kWindowSize / 2, snake_game::kWindowSize * 3 / 4),
                ci::Color("white"),
                ci::Font("Helvetica", 40));
    }

    void SnakeEngine::SetTileTypes() {
        for (vec2 position: snake_.body_) {
            size_t x_spot = (int) position.x;
            size_t y_spot = (int) position.y;
            board_[x_spot][y_spot].type_ = Tile::SNAKE;
        }

        size_t x_food_spot = (int) food_.x;
        size_t y_food_spot = (int) food_.y;
        board_[x_food_spot][y_food_spot].type_ = Tile::FOOD;
        board_[x_food_spot][y_food_spot].color_ = ci::Color("red");
    }

    void SnakeEngine::DrawTiles() {
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
                    ci::gl::color(ci::Color("black"));
                    ci::gl::drawStrokedRect(rect);

                }
            }
        }
    }

    void SnakeEngine::DrawScore() {

        ci::gl::drawStringCentered("SCORE",
                                   score_window_corner + vec2(score_window_size.x / 2, score_window_size.y / 4),
                                   ci::Color("white"),
                                   ci::Font("Helvetica", 40));

        ci::gl::drawStringCentered(std::to_string(snake_.body_.size()),
                                   score_window_corner + vec2(score_window_size.x/2, score_window_size.y * 3 / 5),
                                   ci::Color("white"),
                                   ci::Font("Helvetica", 40));

        ci::gl::color(ci::Color("white"));
        vec2 box_top_corner = score_window_corner;
        vec2 box_bottom_corner = box_top_corner + score_window_size;
        cinder::Rectf rect = ci::Rectf(box_top_corner, box_bottom_corner);
        ci::gl::drawStrokedRoundedRect(rect, 10);

    }

    void SnakeEngine::DrawControls() {

        ci::gl::color(ci::Color("white"));
        vec2 box_top_corner = control_window_corner;
        vec2 box_bottom_corner = control_window_corner + control_window_size;
        cinder::Rectf rect = ci::Rectf(box_top_corner, box_bottom_corner);
        ci::gl::drawStrokedRoundedRect(rect, 10);


        ci::gl::drawStringCentered("KEYS",
                                   control_window_corner + vec2(control_window_size.x/2, control_window_size.y * 1 / 10),
                                   ci::Color("white"),
                                   ci::Font("Helvetica", 40));

        std::vector<std::string> controls = {"up", "down", "left", "right", "restart", "quit"};

        for (size_t i = 0; i < 6; i++) {
            ci::gl::drawString(controls[i],
                               control_window_corner + vec2(control_window_size.x/2 + 5, control_window_size.y * (i + 2) / 8),
                               ci::Color("white"),
                               ci::Font("Helvetica", 25));


            vec2 box_top_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * (i + 2) / 8 - 10);
            vec2 box_bottom_corner = box_top_corner + vec2(36, 36);
            cinder::Rectf rect = ci::Rectf(box_top_corner, box_bottom_corner);
            ci::gl::drawStrokedRoundedRect(rect, 10);
        }

        // Draw up arrow
        ci::gl::color(ci::Color("white"));
        if (snake_.direction_ == Snake::kUp) {
            ci::gl::color(ci::Color("grey"));
        }
        vec2 up_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 2 / 8 - 10);
        ci::gl::drawLine(up_box_corner + vec2(9, 27),
                         up_box_corner + vec2(18, 9));
        ci::gl::drawLine(up_box_corner + vec2(27, 27),
                         up_box_corner + vec2(18, 9));

        // Draw down arrow
        ci::gl::color(ci::Color("white"));
        if (snake_.direction_ == Snake::kDown) {
            ci::gl::color(ci::Color("grey"));
        }
        vec2 down_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 3 / 8 - 10);
        ci::gl::drawLine(down_box_corner + vec2(9, 9),
                        down_box_corner + vec2(18, 27));
        ci::gl::drawLine(down_box_corner + vec2(27, 9),
                         down_box_corner + vec2(18, 27));

        // Draw left arrow
        ci::gl::color(ci::Color("white"));
        if (snake_.direction_ == Snake::kLeft) {
            ci::gl::color(ci::Color("grey"));
        }
        vec2 left_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 4 / 8 - 10);
        ci::gl::drawLine(left_box_corner + vec2(27, 9),
                         left_box_corner + vec2(9, 18));
        ci::gl::drawLine(left_box_corner + vec2(27, 27),
                         left_box_corner + vec2(9, 18));

        // Draw right arrow
        ci::gl::color(ci::Color("white"));
        if (snake_.direction_ == Snake::kRight) {
            ci::gl::color(ci::Color("grey"));
        }
        vec2 right_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 5 / 8 - 10);
        ci::gl::drawLine(right_box_corner + vec2(9, 9),
                         right_box_corner + vec2(27, 18));
        ci::gl::drawLine(right_box_corner + vec2(9, 27),
                         right_box_corner + vec2(27, 18));

        // Draw restart key
        ci::gl::color(ci::Color("white"));
        vec2 restart_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 6 / 8 - 10);
        ci::gl::drawStringCentered("R",
                                   restart_box_corner + vec2(18, 9),
                                   ci::Color("white"),
                                   ci::Font("Helvetica", 30));

        // Draw quit key
        ci::gl::color(ci::Color("white"));
        vec2 quit_box_corner = control_window_corner + vec2(control_window_size.x/5, control_window_size.y * 7 / 8 - 10);
        ci::gl::drawStringCentered("Q",
                                   quit_box_corner + vec2(18, 9),
                                   ci::Color("white"),
                                   ci::Font("Helvetica", 30));

    }

}