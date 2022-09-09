#include "game_controller.hpp"

GameController::GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    name = "Game controller";
    currentApplesCount = 0;

    this->tileSize = tileSize;
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;
    this->minApplesCount = minApplesCount;

    appleSprite = Engine::GetRenderer().CreateSprite("Graphics/apple.png", tileSize, tileSize);

    CreateSnake();
}

GameController::~GameController()
{
    delete(field);
}

std::shared_ptr<Snake> GameController::GetSnake() const { return snake; }

void GameController::CreateField()
{
    field = new char[fieldWidth * fieldHeight];

    for (int i = 0; i < fieldWidth * fieldHeight; i++)
    {
        field[i] = '-';       
    }
}

void GameController::CreateSnake()
{
    std::unique_ptr<SnakeHeadSprites> headSprites = std::make_unique<SnakeHeadSprites>();
    headSprites->headUp = Engine::GetRenderer().CreateSprite("Graphics/head_up.png", tileSize, tileSize);
    headSprites->headDown = Engine::GetRenderer().CreateSprite("Graphics/head_down.png", tileSize, tileSize);
    headSprites->headRight = Engine::GetRenderer().CreateSprite("Graphics/head_right.png", tileSize, tileSize);
    headSprites->headLeft = Engine::GetRenderer().CreateSprite("Graphics/head_left.png", tileSize, tileSize);

    snake = std::make_shared<Snake>(std::move(headSprites));

    snake->position.x = tileSize * fieldWidth / 2;
    snake->position.y = tileSize * fieldHeight / 2;
}

void GameController::Update(double elapsedTime)
{
    while(currentApplesCount < minApplesCount) AddApple();   
}

void GameController::OnNotify(std::shared_ptr<SnakeEvent> message)
{
    if(message->Type() == SnakeEventType::AppleEaten) currentApplesCount--;
}

void GameController::AddApple()
{
    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(appleSprite);

    Vector2D position = GetFreePosition();

    newApple->position.x = position.x;
    newApple->position.y = position.y;

    currentApplesCount++;

    Engine::AddObject(newApple);
}

Vector2D GameController::GetFreePosition()
{
    std::srand(std::time(nullptr));

    //random position on field
    Vector2D newPosition;
    newPosition.x = (std::rand() % fieldWidth) * tileSize;
    newPosition.y = (std::rand() % fieldHeight) * tileSize;

    std::cout << "new apple position (x): " << newPosition.x << std::endl;
    std::cout << "new apple position (y): " << newPosition.y << std::endl;

    return newPosition;
}