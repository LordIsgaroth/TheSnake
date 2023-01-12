#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "snake_game_objects.hpp"

class GameController : public SceneObject
{
public:
    GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);

    std::shared_ptr<Snake> GetSnake() const { return snake; }
    const std::vector<std::shared_ptr<Border>>& GetBorders() const { return borders; }
    const std::vector<std::shared_ptr<GameObject>>& GetField() const { return fieldTiles; } 
    std::shared_ptr<TextObject> GetScoreText() const { return scoreText; }

    void CreateSnake();

private:
    double movementDuration = 0;
    double maxMovementDuration = 100;

    int score = 0;

    int minApplesCount, currentApplesCount;

    int fieldWidth, fieldHeight;
    int tileSize;
    int scoreFieldSize;

    std::vector<Vector2D> field;
    std::vector<Vector2D> freePositions;
   
    std::shared_ptr<TextObject> scoreText;
    std::shared_ptr<Button> playAgainButton;

    std::shared_ptr<Snake> snake;
    std::shared_ptr<Sprite> appleSprite;
    std::vector<std::shared_ptr<Border>> borders;
    std::vector<std::shared_ptr<GameObject>> fieldTiles;
    
    void CreateField();
    void CreateBorders();
    void CreateScoreText();
    void CreatePlayAgainButton();

    void AppleEaten();
    void AddApple();
    void UpdateScore();
    void ShowPlayAgainButton();
    void PlayAgain();

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder); 

    void DefineFreePositions();
    Vector2D GetRandomFreePosition();

    void Update(double elapsedTime) override;  
};