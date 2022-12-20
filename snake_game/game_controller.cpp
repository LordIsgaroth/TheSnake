 #include "game_controller.hpp"

GameController::GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    scoreFieldSize = 2 * tileSize;

    name = "Game controller";
    currentApplesCount = 0;
    score = 0;

    this->tileSize = tileSize;
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;
    this->minApplesCount = minApplesCount;

    appleSprite = std::make_shared<Sprite>("Graphics/apple.png");

    CreateField();
    CreateBorders();
    CreateScoreText();
}

void GameController::CreateScoreText()
{
    std::unique_ptr<Text> text = std::make_unique<Text>("Graphics/score_font.ttf", 40, "Score: 0");

    std::unique_ptr<LabelRenderer> labelRenderer = std::make_unique<LabelRenderer>(std::move(text), 300, 60, 100, true);

    scoreText = std::make_shared<TextObject>("Score text", std::move(labelRenderer));
    scoreText->position = Vector2D(((2 * tileSize + fieldWidth * tileSize) / 2) - 150, 0);
}

void GameController::CreateField()
{
    std::shared_ptr<Sprite> grassSprite = std::make_shared<Sprite>("Graphics/grass.png");

    for (int i = 0; i < fieldWidth * fieldHeight; i++)
    {
        std::shared_ptr<Grass> grass = std::make_shared<Grass>(CreateTileSpriteRenderer(grassSprite, 0));
        int x = tileSize + (i % fieldWidth) * tileSize;
        int y = scoreFieldSize + tileSize + (i / fieldWidth) * tileSize;

        Vector2D position = Vector2D(x, y);

        grass->position = Vector2D(x, y);

        field.push_back(position);
        fieldTiles.push_back(grass);
    }    
}

void GameController::CreateBorders()
{
    std::shared_ptr<Sprite> topBorderSprite = std::make_shared<Sprite>("Graphics/border_top.png");
    std::shared_ptr<Sprite> bottomBorderSprite = std::make_shared<Sprite>("Graphics/border_bottom.png");
    std::shared_ptr<Sprite> leftBorderSprite = std::make_shared<Sprite>("Graphics/border_left.png");
    std::shared_ptr<Sprite> rightBorderSprite = std::make_shared<Sprite>("Graphics/border_right.png");

    std::shared_ptr<Sprite> topLeftCornerSprite = std::make_shared<Sprite>("Graphics/border_top_left_corner.png");
    std::shared_ptr<Sprite> topRightCornerSprite = std::make_shared<Sprite>("Graphics/border_top_right_corner.png");
    std::shared_ptr<Sprite> bottomLeftCornerSprite = std::make_shared<Sprite>("Graphics/border_bottom_left_corner.png");
    std::shared_ptr<Sprite> bottomRightCornerSprite = std::make_shared<Sprite>("Graphics/border_bottom_right_corner.png");  

    std::shared_ptr<Border> topLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topLeftCornerSprite, 3));
    topLeftCorner->position = Vector2D(0, scoreFieldSize);

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topRightCornerSprite, 3));
    topRightCorner->position = Vector2D(tileSize + fieldWidth * tileSize, scoreFieldSize);

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomLeftCornerSprite, 3));
    bottomLeftCorner->position = Vector2D(0, scoreFieldSize + tileSize + fieldHeight * tileSize);

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomRightCornerSprite, 3));
    bottomRightCorner->position = Vector2D(tileSize + fieldWidth * tileSize, scoreFieldSize + tileSize + fieldHeight * tileSize);

    borders.push_back(topLeftCorner);
    borders.push_back(topRightCorner);
    borders.push_back(bottomLeftCorner);
    borders.push_back(bottomRightCorner);

    for (int i = 0; i < fieldWidth; i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(CreateTileSpriteRenderer(topBorderSprite, 3));
        topBorder->position = Vector2D(tileSize + i * tileSize, scoreFieldSize);

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(CreateTileSpriteRenderer(bottomBorderSprite, 3));
        bottomBorder->position = Vector2D(tileSize + i * tileSize, scoreFieldSize + tileSize + fieldHeight * tileSize);

        borders.push_back(topBorder);
        borders.push_back(bottomBorder);
    }

    for (int i = 0; i < fieldHeight; i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(CreateTileSpriteRenderer(leftBorderSprite, 3));
        leftBorder->position = Vector2D(0, scoreFieldSize+ tileSize + i * tileSize);

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(CreateTileSpriteRenderer(rightBorderSprite, 3));
        rightBorder->position = Vector2D(tileSize + fieldWidth * tileSize, scoreFieldSize + tileSize + i * tileSize);

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
    if (message->Type() == SnakeEventType::AppleEaten) 
    {
        currentApplesCount--;
        score++;
        UpdateScore();
    }
}

void GameController::AddApple()
{
    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(CreateTileSpriteRenderer(appleSprite, 1));
    newApple->position = GetRandomFreePosition();

    currentApplesCount++;

    Engine::AddObject(newApple);
}

void GameController::DefineFreePositions()
{
    freePositions.clear();

    for (Vector2D position : field)
    {
        freePositions.push_back(position);
    }

    for (SnakeSegment* segment : snake->GetSegments())
    {
        auto pos = std::find(freePositions.begin(), freePositions.end(), segment->position); 

        if(pos != freePositions.end())
        {
            freePositions.erase(pos);
        }
    }
}

Vector2D GameController::GetRandomFreePosition()
{
    std::srand(std::time(nullptr));
    DefineFreePositions();

    Vector2D newPosition = freePositions[std::rand() % (freePositions.size() - 1)];
    
    std::cout << "new apple position (x): " << newPosition.X() << std::endl;
    std::cout << "new apple position (y): " << newPosition.Y() << std::endl;

    return newPosition;
}

void GameController::UpdateScore()
{
    scoreText->SetText("Score: " + std::to_string(score));
}    