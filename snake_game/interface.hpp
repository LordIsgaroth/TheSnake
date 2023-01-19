#pragma once

#include "my_little_engine/my_little_engine.hpp"
#include "snake_game_objects.hpp"

class Interface
{
public:
    Interface() {}

    boost::signals2::signal<void()> PlayAgainPressed;

    void CreateScoreLabel(Vector2D position);
    void CreateGameOverLabel(Vector2D position);    
    void CreatePlayAgainButton(int tileSize, int fieldWidth, int fieldHeight);

    void Load();

    void UpdateScore(int score);
    void ShowPlayAgain();

private:

    bool loaded = false;

    std::shared_ptr<TextObject> scoreLabel;
    std::shared_ptr<TextObject> gameOverLabel;
    std::shared_ptr<TextObject> playAgainLabel;
    std::shared_ptr<Button> playAgainButton;

    void HidePlayAgain();
    void PlayAgain();
};