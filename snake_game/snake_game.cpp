#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Load()
{
    Engine::Initialize("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<GameController> gameController = std::make_shared<GameController>(TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT, MIN_APPLES);

    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
    objectsForLoading->push_back(gameController);

    for (std::shared_ptr<Border> border : gameController->GetBorders())
    {
        objectsForLoading->push_back(border);
    }

    for (std::shared_ptr<GameObject> grass : gameController->GetField())
    {
        objectsForLoading->push_back(grass);
    }

    objectsForLoading->push_back(gameController->GetScoreText());

    mainScene = std::make_shared<Scene>("Main scene", std::move(objectsForLoading));

    Engine::LoadScene(mainScene);

    gameController->CreateSnake();
}

void SnakeGame::Start()
{
    Engine::Start();
}