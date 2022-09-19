#include "game_controller.hpp"

GameController::GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    name = "Game controller";
    currentApplesCount = 0;

    this->tileSize = tileSize;
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;
    this->minApplesCount = minApplesCount;

    appleSprite = Engine::GetRenderer().CreateSprite("Graphics/apple.png");

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
    std::shared_ptr<Sprite> grassSprite = Engine::GetRenderer().CreateSprite("Graphics/grass.png");
    
    field = new char[fieldWidth * fieldHeight];

    for (int i = 0; i < fieldWidth * fieldHeight; i++)
    {
        field[i] = '-';

        std::shared_ptr<Grass> grass = std::make_shared<Grass>(CreateTileSpriteRenderer(grassSprite, 0));
        int x = tileSize + (i % fieldWidth) * tileSize;
        int y = tileSize + (i / fieldWidth) * tileSize;

        grass->SetPosition(Vector2D(x, y));

        fieldTiles.push_back(grass);
    }    
}

void GameController::CreateBorders()
{
    std::shared_ptr<Sprite> topBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top.png");
    std::shared_ptr<Sprite> bottomBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom.png");
    std::shared_ptr<Sprite> leftBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_left.png");
    std::shared_ptr<Sprite> rightBorderSprite = Engine::GetRenderer().CreateSprite("Graphics/border_right.png");

    std::shared_ptr<Sprite> topLeftCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top_left_corner.png");
    std::shared_ptr<Sprite> topRightCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_top_right_corner.png");
    std::shared_ptr<Sprite> bottomLeftCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom_left_corner.png");
    std::shared_ptr<Sprite> bottomRightCornerSprite = Engine::GetRenderer().CreateSprite("Graphics/border_bottom_right_corner.png");  

    std::shared_ptr<Border> topLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topLeftCornerSprite, 3));
    topLeftCorner->SetPosition(Vector2D(0, 0));

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topRightCornerSprite, 3));
    topRightCorner->SetPosition(Vector2D(tileSize + fieldWidth * tileSize, 0));

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomLeftCornerSprite, 3));
    bottomLeftCorner->SetPosition(Vector2D(0, tileSize + fieldHeight * tileSize));

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomRightCornerSprite, 3));
    bottomRightCorner->SetPosition(Vector2D(tileSize + fieldWidth * tileSize, tileSize + fieldHeight * tileSize));

    borders.push_back(topLeftCorner);
    borders.push_back(topRightCorner);
    borders.push_back(bottomLeftCorner);
    borders.push_back(bottomRightCorner);

    for (int i = 0; i < fieldWidth; i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(CreateTileSpriteRenderer(topBorderSprite, 3));
        topBorder->SetPosition(Vector2D(tileSize + i * tileSize, 0));

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(CreateTileSpriteRenderer(bottomBorderSprite, 3));
        bottomBorder->SetPosition(Vector2D(tileSize + i * tileSize, tileSize + fieldHeight * tileSize));

        borders.push_back(topBorder);
        borders.push_back(bottomBorder);
    }

    for (int i = 0; i < fieldHeight; i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(CreateTileSpriteRenderer(leftBorderSprite, 3));
        leftBorder->SetPosition(Vector2D(0, tileSize + i * tileSize));

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(CreateTileSpriteRenderer(rightBorderSprite, 3));
        rightBorder->SetPosition(Vector2D(tileSize + fieldWidth * tileSize, tileSize + i * tileSize));

        borders.push_back(leftBorder);
        borders.push_back(rightBorder);
    } 
}

void GameController::CreateSnake()
{
    std::unique_ptr<SnakeHeadSprites> headSprites = std::make_unique<SnakeHeadSprites>();
    headSprites->headUp = Engine::GetRenderer().CreateSprite("Graphics/head_up.png");
    headSprites->headDown = Engine::GetRenderer().CreateSprite("Graphics/head_down.png");
    headSprites->headRight = Engine::GetRenderer().CreateSprite("Graphics/head_right.png");
    headSprites->headLeft = Engine::GetRenderer().CreateSprite("Graphics/head_left.png");

    snake = std::make_shared<Snake>(CreateTileSpriteRenderer(headSprites->headRight, 2), std::move(headSprites));
    snake->SetPosition(Vector2D(tileSize * fieldWidth / 2, tileSize * fieldHeight / 2));
}

std::unique_ptr<SpriteRenderer> GameController::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder));
}

void GameController::Update(double elapsedTime)
{
    while(currentApplesCount < minApplesCount) AddApple();

    ChangeSnakeDirection();   
}

void GameController::ChangeSnakeDirection()
{
    Vector2D snakeDirection = snake->GetDirection();
    Vector2D snakePosition = snake->GetPosition();

    if (snakeDirection == Vector2D::Right())
    {
        int tileX = snakePosition.x / tileSize;
        
        if (snakePosition.x > (tileX * tileSize + (tileSize * maxChangeDir)))
        {
            snake->SetPosition(Vector2D(tileX * tileSize + tileSize, snakePosition.y));
            snake->SetNextDirection();
        }
    }
    else if (snakeDirection == Vector2D::Left())
    {
        int tileX = snakePosition.x / tileSize;
        
        if (snakePosition.x < (tileX * tileSize + (tileSize * minChangeDir)))
        {
            snake->SetPosition(Vector2D(tileX * tileSize, snakePosition.y));
            snake->SetNextDirection();
        }
    }
    else if (snakeDirection == Vector2D::Up())
    {
        int tileY = snakePosition.y / tileSize;

        if (snakePosition.y < (tileY * tileSize + (tileSize * minChangeDir)))
        {
            snake->SetPosition(Vector2D(snakePosition.x, tileY * tileSize));
            snake->SetNextDirection();
        }
    }
    else if (snakeDirection == Vector2D::Down())
    {
        int tileY = snakePosition.y / tileSize;

        if (snakePosition.y > (tileY * tileSize + (tileSize * maxChangeDir)))
        {
            snake->SetPosition(Vector2D(snakePosition.x, tileY * tileSize + tileSize));
            snake->SetNextDirection();
        }
    }
    else
    {
        snake->SetNextDirection();
    }
}

void GameController::OnNotify(std::shared_ptr<SnakeEvent> message)
{
    if(message->Type() == SnakeEventType::AppleEaten) currentApplesCount--;
}

void GameController::AddApple()
{
    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(CreateTileSpriteRenderer(appleSprite, 1));
    newApple->SetPosition(GetFreePosition());

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