#include "snake_game.hpp"

SnakeGame::SnakeGame() 
{
    Vector2D levelPosition(0, 2 * TILE_SIZE);
    level = std::make_unique<Level>(levelPosition, TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT, MIN_APPLES);
    interface = std::make_unique<Interface>();
}

void SnakeGame::Load()
{
    Engine::Initialize("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
  
    mainScene = std::make_shared<Scene>("Main scene", std::move(objectsForLoading));

    Engine::LoadScene(mainScene);

    Vector2D scoreLabelPosition(((2 * TILE_SIZE + FIELD_WIDTH * TILE_SIZE) / 2) - 150, 0);
    Vector2D gameOverLabelPosition(((2 * TILE_SIZE + FIELD_WIDTH * TILE_SIZE) / 2) - 200, 200);

    
    interface->CreateScoreLabel(scoreLabelPosition);
    interface->CreateGameOverLabel(gameOverLabelPosition);
    interface->CreatePlayAgainButton(TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT);

    level->ScoreChanged.connect(boost::bind(&Interface::UpdateScore, interface.get(), boost::placeholders::_1));
    level->GameOver.connect(boost::bind(&Interface::ShowPlayAgain, interface.get()));
    interface->PlayAgainPressed.connect(boost::bind(&Level::Reload, level.get()));

    level->Load();
    interface->Load();
}

void SnakeGame::Start()
{
    Engine::Start();
}