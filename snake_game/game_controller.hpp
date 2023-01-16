#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "snake_game_objects.hpp"
#include "field.hpp"
#include "apple_spawner.hpp"

//Ответственности класса
//
//Управление скоростью движения змеи и вызов этого движения
//Управление начислеием очков
//Создание яблок
//Создание змеи
//Управление перезапуском игры
//Управление интерфейсом

class GameController : public SceneObject
{
public:
    GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);

    std::shared_ptr<Snake> GetSnake() const { return snake; }
    const std::vector<std::shared_ptr<Border>>& GetBorders() const { return field->GetBorderTiles(); }
    const std::vector<std::shared_ptr<GameObject>>& GetField() const { return field->GetFieldTiles(); } 
    std::shared_ptr<TextObject> GetScoreLabel() const { return scoreLabel; }
    std::shared_ptr<TextObject> GetGameOverLabel() const { return gameOverLabel; }
    std::shared_ptr<TextObject> GetPlayAgainLabel() const { return playAgainLabel; }

    void CreateSnake();

private:
    double movementDuration = 0;
    double maxMovementDuration = 100;

    int score = 0;

    int fieldWidth, fieldHeight;
    int tileSize;
    int scoreFieldSize;

    std::shared_ptr<Field> field;
    std::shared_ptr<AppleSpawner> appleSpawner;
   
    std::shared_ptr<TextObject> scoreLabel;
    std::shared_ptr<TextObject> gameOverLabel;
    std::shared_ptr<TextObject> playAgainLabel;
    ;
    std::shared_ptr<Button> playAgainButton;

    std::shared_ptr<Snake> snake;    
    
    void Update(double elapsedTime) override;
    
    void CreateTexts();
    void CreatePlayAgainButton();

    void AppleEaten();
    void UpdateScore();
    void ShowPlayAgain();
    void PlayAgain();

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder);
};