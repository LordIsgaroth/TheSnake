#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "snake_game_objects.hpp"

class GameController : public GameObject, public IObserver<std::shared_ptr<SnakeEvent>>
{
public:
    GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);

    std::shared_ptr<Snake> GetSnake() const;
    const std::vector<std::shared_ptr<Border>>& GetBorders() const;
    const std::vector<std::shared_ptr<GameObject>>& GetField() const { return fieldTiles; } 

    void CreateSnake();

private:
    const float minChangeDir = 0.15;
    const float maxChangeDir = 0.85;

    double movementDuration = 0;
    double maxMovementDuration = 100;

    int minApplesCount, currentApplesCount;

    int fieldWidth, fieldHeight;
    int tileSize;

    std::vector<Vector2D> field;
    std::vector<Vector2D> freePositions;
   
    std::shared_ptr<Snake> snake;
    std::shared_ptr<Sprite> appleSprite;
    std::vector<std::shared_ptr<Border>> borders;
    std::vector<std::shared_ptr<GameObject>> fieldTiles;
    
    void CreateField();
    void CreateBorders();

    void AddApple();

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder); 

    void DefineFreePositions();
    Vector2D GetRandomFreePosition();

    void Update(double elapsedTime) override;
    void OnNotify(std::shared_ptr<SnakeEvent> message) override;

};