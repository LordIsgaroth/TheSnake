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
    std::shared_ptr<TextObject> GetScoreLabel() const { return scoreLabel; }
    std::shared_ptr<TextObject> GetGameOverLabel() const { return gameOverLabel; }
    std::shared_ptr<TextObject> GetPlayAgainLabel() const { return playAgainLabel; }

    void CreateSnake();

private:
    double movementDuration = 0;
    double maxMovementDuration = 100;

    int score = 0;

    int minApplesCount, currentApplesCount;

    int fieldWidth, fieldHeight;
    int tileSize;
    int scoreFieldSize;

    //Change to collection for multiple apples
    const Apple* apple;

    std::vector<Vector2D> field;
    std::vector<Vector2D> freePositions;
   
    std::shared_ptr<TextObject> scoreLabel;
    std::shared_ptr<TextObject> gameOverLabel;
    std::shared_ptr<TextObject> playAgainLabel;
    ;
    std::shared_ptr<Button> playAgainButton;

    std::shared_ptr<Snake> snake;
    std::shared_ptr<Sprite> appleSprite;
    std::vector<std::shared_ptr<Border>> borders;
    std::vector<std::shared_ptr<GameObject>> fieldTiles;
    
    void CreateField();
    void CreateBorders();
    void CreateTexts();
    void CreatePlayAgainButton();

    void AppleEaten();
    void AddApple();
    void UpdateScore();
    void ShowPlayAgain();
    void PlayAgain();

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder); 

    void DefineFreePositions();
    Vector2D GetRandomFreePosition();

    void Update(double elapsedTime) override;  
};