#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Load()
{
    Engine::Initialize("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<Level> level = std::make_shared<Level>(TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT, MIN_APPLES);

    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
    objectsForLoading->push_back(level);

    mainScene = std::make_shared<Scene>("Main scene", std::move(objectsForLoading));

    Engine::LoadScene(mainScene);

    Vector2D scoreLabelPosition(((2 * TILE_SIZE + FIELD_WIDTH * TILE_SIZE) / 2) - 150, 0);
    Vector2D gameOverLabelPosition(((2 * TILE_SIZE + FIELD_WIDTH * TILE_SIZE) / 2) - 200, 200);

    interface = Interface();
    interface.CreateScoreLabel(scoreLabelPosition);
    interface.CreateGameOverLabel(gameOverLabelPosition);
    interface.CreatePlayAgainButton(TILE_SIZE, FIELD_WIDTH, FIELD_HEIGHT);

    level->ScoreChanged.connect(boost::bind(&Interface::UpdateScore, &interface, boost::placeholders::_1));
    level->GameOver.connect(boost::bind(&Interface::ShowPlayAgain, &interface));
    interface.PlayAgainPressed.connect(boost::bind(&Level::PlayAgain, level.get()));
    //AppleSpawned.connect(boost::bind(&Field::TakePosition, field.get(), boost::placeholders::_1));

    level->Load();
    interface.Load();
    //level->CreateSnake();
}

void SnakeGame::Start()
{
    Engine::Start();
}