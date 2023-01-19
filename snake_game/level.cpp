 #include "level.hpp"

Level::Level(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    scoreFieldSize = 2 * tileSize;

    name = "Game controller";
    score = 0;
    loaded = false;

    this->tileSize = tileSize;
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;

    int applesRenderingOrder = 1;

    field = std::make_shared<Field>(Vector2D(0, scoreFieldSize), tileSize, fieldWidth, fieldHeight);
    appleSpawner = std::make_shared<AppleSpawner>(minApplesCount, tileSize, applesRenderingOrder);
    appleSpawner->AppleSpawned.connect(boost::bind(&Field::TakePosition, field.get(), boost::placeholders::_1));

    CreateBorders();
}

void Level::Load()
{
    if (loaded) return;

    LoadBorders();

    for (std::shared_ptr<GameObject> grass : field->GetFieldTiles())
    {
        Engine::AddObject(grass);
    }

    CreateBorders();
    CreateSnake();

    loaded = true;
}

void Level::CreateBorders()
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
    topLeftCorner->position = Vector2D(0, field->Position().Y());

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topRightCornerSprite, 3));
    topRightCorner->position = Vector2D(tileSize + field->Width() * tileSize, field->Position().Y());

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomLeftCornerSprite, 3));
    bottomLeftCorner->position = Vector2D(0, field->Position().Y() + tileSize + field->Height() * tileSize);

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomRightCornerSprite, 3));
    bottomRightCorner->position = Vector2D(tileSize + field->Width() * tileSize, field->Position().Y() + tileSize + field->Height() * tileSize);

    borderTiles.push_back(topLeftCorner);
    borderTiles.push_back(topRightCorner);
    borderTiles.push_back(bottomLeftCorner);
    borderTiles.push_back(bottomRightCorner);

    for (int i = 0; i < field->Width(); i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(CreateTileSpriteRenderer(topBorderSprite, 3));
        topBorder->position = Vector2D(tileSize + i * tileSize, field->Position().Y());

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(CreateTileSpriteRenderer(bottomBorderSprite, 3));
        bottomBorder->position = Vector2D(tileSize + i * tileSize, field->Position().Y() + tileSize + field->Height() * tileSize);

        borderTiles.push_back(topBorder);
        borderTiles.push_back(bottomBorder);
    }

    for (int i = 0; i < field->Height(); i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(CreateTileSpriteRenderer(leftBorderSprite, 3));
        leftBorder->position = Vector2D(0, field->Position().Y() + tileSize + i * tileSize);

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(CreateTileSpriteRenderer(rightBorderSprite, 3));
        rightBorder->position = Vector2D(tileSize + field->Width() * tileSize, field->Position().Y() + tileSize + i * tileSize);

        borderTiles.push_back(leftBorder);
        borderTiles.push_back(rightBorder);
    } 
}

void Level::CreateSnake()
{
    Vector2D snakePosition(tileSize * fieldWidth / 2, tileSize * fieldHeight / 2);

    snake = std::make_shared<Snake>(CreateTileSpriteRenderer(nullptr, 2), snakePosition, Vector2D::Right());
    //snake->OnAppleEaten.connect(boost::bind(&Field::RemoveApple, *(field.get()), boost::placeholders::_1));
    snake->OnAppleEaten.connect(boost::bind(&Level::AppleEaten, this, boost::placeholders::_1));
    snake->OnSnakeDead.connect(boost::bind(&Level::ShowPlayAgain, this));
    Engine::AddObject(snake);
}

void Level::LoadBorders()
{
    for (std::shared_ptr<Border> object : borderTiles)
    {
        Engine::AddObject(object);
    }    
}

void Level::ShowPlayAgain()
{
    GameOver();
}

std::unique_ptr<SpriteRenderer> Level::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder, true));
}

void Level::Update(double elapsedTime)
{
    appleSpawner->SpawnApples(field->GetFreePositions());
    
    movementDuration += elapsedTime;

    if (movementDuration >= maxMovementDuration)
    {
        movementDuration = 0;
        snake->Move(); 
    }

    //std::cout << movementDuration << std::endl;
}

void Level::AppleEaten(Vector2D position)
{

    appleSpawner->ReduceCurrentApplesCount();
    appleSpawner->SpawnApples(field->GetFreePositions());
    field->ReleasePosition(position);

    score++;
    ScoreChanged(score);
}

void Level::PlayAgain()
{
    snake->Destroy();

    CreateSnake();

    score = 0;
    ScoreChanged(score);

    // Engine::RemoveObject(apple->Id());
    // currentApplesCount--;

    // AddApple();
}