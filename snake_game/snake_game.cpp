#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Start()
{
    Engine::Initialize("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<GameController> gameController = std::make_shared<GameController>(TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT, MIN_APPLES);

    gameController->GetSnake()->Attach(gameController);

    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
    objectsForLoading->push_back(gameController);
    objectsForLoading->push_back(gameController->GetSnake());

    for(std::shared_ptr<Border> border : gameController->GetBorders())
    {
        objectsForLoading->push_back(border);
    }

    std::shared_ptr<Scene> mainScene = std::make_shared<Scene>("Main scene", std::move(objectsForLoading));

    Engine::LoadScene(mainScene);
    Engine::Start();
}