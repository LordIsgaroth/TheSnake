#pragma once

#include <memory>
#include <unordered_map>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "apple.hpp"

class GameController : public GameObject, public IObserver<std::shared_ptr<SnakeEvent>>
{
public:
    GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);
    ~GameController();

    std::shared_ptr<Snake> GetSnake() const;

private:
    int minApplesCount, currentApplesCount;

    int fieldWidth, fieldHeight;
    int tileSize;

    char* field;

    std::shared_ptr<Snake> snake;
    std::shared_ptr<Sprite> appleSprite;

    void CreateField();
    void CreateSnake();
    void AddApple();

    Vector2D GetFreePosition();

    void Update(double elapsedTime) override;
    void OnNotify(std::shared_ptr<SnakeEvent> message) override;

};