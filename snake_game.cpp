#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Start()
{
    Engine::Initialize("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<Apple> apple = std::make_shared<Apple>(Engine::GetRenderer().CreateSprite("Graphics/apple.png"));

    apple->posX = 100;
    apple->posY = 100;

    std::unique_ptr<SnakeHeadSprites> headSprites = std::make_unique<SnakeHeadSprites>();
    headSprites->headUp = Engine::GetRenderer().CreateSprite("Graphics/head_up.png");
    headSprites->headDown = Engine::GetRenderer().CreateSprite("Graphics/head_down.png");
    headSprites->headRight = Engine::GetRenderer().CreateSprite("Graphics/head_right.png");
    headSprites->headLeft = Engine::GetRenderer().CreateSprite("Graphics/head_left.png");

    std::shared_ptr<Snake> snake = std::make_shared<Snake>(std::move(headSprites));

    snake->posX = (SCREEN_WIDTH - snake->GetSprite()->Width()) / 2;
    snake->posY = (SCREEN_HEIGHT - snake->GetSprite()->Height()) / 2;

    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
    objectsForLoading->push_back(snake);
    objectsForLoading->push_back(apple);

    std::shared_ptr<Scene> mainScene = std::make_shared<Scene>("Main scene", std::move(objectsForLoading));

    Engine::LoadScene(mainScene);
    Engine::Start();
}