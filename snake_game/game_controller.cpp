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


    CreateField();
    CreateBorders();
    CreateSnake();
}

GameController::~GameController()
{
    delete(field);
}

std::shared_ptr<Snake> GameController::GetSnake() const { return snake; }
const std::vector<std::shared_ptr<Border>>& GameController::GetBorders() const { return borders; }


void GameController::CreateField()
{
    field = new char[fieldWidth * fieldHeight];

    for (int i = 0; i < fieldWidth * fieldHeight; i++)
    {
        field[i] = '-';       
    }
}

void GameController::CreateBorders()
{
    std::shared_ptr<Sprite> topBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top.png", tileSize, tileSize);
    std::shared_ptr<Sprite> bottomBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom.png", tileSize, tileSize);
    std::shared_ptr<Sprite> leftBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_left.png", tileSize, tileSize);
    std::shared_ptr<Sprite> rightBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_right.png", tileSize, tileSize);

    std::shared_ptr<Sprite> topLeftCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top_left_corner.png", tileSize, tileSize);
    std::shared_ptr<Sprite> topRightCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top_right_corner.png", tileSize, tileSize);
    std::shared_ptr<Sprite> bottomLeftCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom_left_corner.png", tileSize, tileSize);
    std::shared_ptr<Sprite> bottomRightCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom_right_corner.png", tileSize, tileSize);

    std::shared_ptr<Border> topLeftCorner = std::make_shared<Border>(topLeftCornerSprite);
    topLeftCorner->position.x = 0;
    topLeftCorner->position.y = 0;

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(topRightCornerSprite);
    topRightCorner->position.x = tileSize + fieldWidth * tileSize;
    topRightCorner->position.y = 0;

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(bottomLeftCornerSprite);
    bottomLeftCorner->position.x = 0;
    bottomLeftCorner->position.y = tileSize + fieldHeight * tileSize;

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(bottomRightCornerSprite);
    bottomRightCorner->position.x = tileSize + fieldWidth * tileSize;
    bottomRightCorner->position.y = tileSize + fieldHeight * tileSize;    

    borders.push_back(topLeftCorner);
    borders.push_back(topRightCorner);
    borders.push_back(bottomLeftCorner);
    borders.push_back(bottomRightCorner);

    for (int i = 0; i < fieldWidth; i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(topBorderSprite);
        topBorder->position.x = tileSize + i * tileSize;
        topBorder->position.y = 0;

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(bottomBorderSprite);
        bottomBorder->position.x = tileSize + i * tileSize;
        bottomBorder->position.y = tileSize + fieldHeight * tileSize;

        borders.push_back(topBorder);
        borders.push_back(bottomBorder);
    }

    for (int i = 0; i < fieldHeight; i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(leftBorderSprite);
        leftBorder->position.x = 0;
        leftBorder->position.y = tileSize + i * tileSize;

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(rightBorderSprite);
        rightBorder->position.x = tileSize + fieldWidth * tileSize;
        rightBorder->position.y = tileSize + i * tileSize;

        borders.push_back(leftBorder);
        borders.push_back(rightBorder);
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
    newPosition.x = tileSize + (std::rand() % fieldWidth) * tileSize;
    newPosition.y = tileSize + (std::rand() % fieldHeight) * tileSize;

    std::cout << "new apple position (x): " << newPosition.x << std::endl;
    std::cout << "new apple position (y): " << newPosition.y << std::endl;

    return newPosition;
}