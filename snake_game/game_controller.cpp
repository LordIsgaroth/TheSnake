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
}

GameController::~GameController()
{
    delete(field);
}

std::shared_ptr<Snake> GameController::GetSnake() const { return snake; }
const std::vector<std::shared_ptr<Border>>& GameController::GetBorders() const { return borders; }

void GameController::CreateField()
{
    std::shared_ptr<Sprite> grassSprite = Engine::GetRenderer().CreateSprite("Graphics/grass.png", tileSize, tileSize);
    
    field = new char[fieldWidth * fieldHeight];

    for (int i = 0; i < fieldWidth * fieldHeight; i++)
    {
        field[i] = '-';

        std::shared_ptr<Grass> grass = std::make_shared<Grass>(CreateTileSpriteRenderer(grassSprite, 0));
        int x = tileSize + (i % fieldWidth) * tileSize;
        int y = tileSize + (i / fieldWidth) * tileSize;

        grass->position = Vector2D(x, y);

        fieldTiles.push_back(grass);
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

    std::shared_ptr<Border> topLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topLeftCornerSprite, 3));
    topLeftCorner->position = Vector2D(0, 0);

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topRightCornerSprite, 3));
    topRightCorner->position = Vector2D(tileSize + fieldWidth * tileSize, 0);

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomLeftCornerSprite, 3));
    bottomLeftCorner->position = Vector2D(0, tileSize + fieldHeight * tileSize);

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomRightCornerSprite, 3));
    bottomRightCorner->position = Vector2D(tileSize + fieldWidth * tileSize, tileSize + fieldHeight * tileSize);

    borders.push_back(topLeftCorner);
    borders.push_back(topRightCorner);
    borders.push_back(bottomLeftCorner);
    borders.push_back(bottomRightCorner);

    for (int i = 0; i < fieldWidth; i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(CreateTileSpriteRenderer(topBorderSprite, 3));
        topBorder->position = Vector2D(tileSize + i * tileSize, 0);

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(CreateTileSpriteRenderer(bottomBorderSprite, 3));
        bottomBorder->position = Vector2D(tileSize + i * tileSize, tileSize + fieldHeight * tileSize);

        borders.push_back(topBorder);
        borders.push_back(bottomBorder);
    }

    for (int i = 0; i < fieldHeight; i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(CreateTileSpriteRenderer(leftBorderSprite, 3));
        leftBorder->position = Vector2D(0, tileSize + i * tileSize);

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(CreateTileSpriteRenderer(rightBorderSprite, 3));
        rightBorder->position = Vector2D(tileSize + fieldWidth * tileSize, tileSize + i * tileSize);

        borders.push_back(leftBorder);
        borders.push_back(rightBorder);
    } 
}

void GameController::CreateSnake()
{
    Vector2D snakePosition(tileSize * fieldWidth / 2, tileSize * fieldHeight / 2);

    snake = std::make_shared<Snake>(CreateTileSpriteRenderer(nullptr, 2), snakePosition, Vector2D::Right());
    Engine::AddObject(snake);
}

std::unique_ptr<SpriteRenderer> GameController::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder, true));
}

void GameController::Update(double elapsedTime)
{
    while(currentApplesCount < minApplesCount) AddApple();

    movementDuration += elapsedTime;

    if (movementDuration >= maxMovementDuration)
    {
        movementDuration = 0;
        snake->Move(); 
    }

    //std::cout << movementDuration << std::endl;
}

void GameController::OnNotify(std::shared_ptr<SnakeEvent> message)
{
    if (message->Type() == SnakeEventType::AppleEaten) currentApplesCount--;
}

void GameController::AddApple()
{
    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(CreateTileSpriteRenderer(appleSprite, 1));
    newApple->position = GetFreePosition();

    currentApplesCount++;

    Engine::AddObject(newApple);
}

Vector2D GameController::GetFreePosition()
{
    std::srand(std::time(nullptr));

    //random position on field

    double newPosX = tileSize + (std::rand() % fieldWidth) * tileSize;
    double newPosY = tileSize + (std::rand() % fieldHeight) * tileSize;

    Vector2D newPosition(newPosX, newPosY);
    
    std::cout << "new apple position (x): " << newPosition.X() << std::endl;
    std::cout << "new apple position (y): " << newPosition.Y() << std::endl;

    return newPosition;
}