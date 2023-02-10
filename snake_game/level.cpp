 #include "level.hpp"

Level::Level(Vector2D position, int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    score = 0;
    loaded = false;

    this->position = position;
    this->tileSize = tileSize;
 
    appleStorage = AppleStorage(minApplesCount);

    int applesRenderingOrder = 1;

    field = std::make_shared<Field>(Vector2D(position.X(), position.Y()), tileSize, fieldWidth, fieldHeight);
    appleSpawner = std::make_shared<AppleSpawner>(tileSize, applesRenderingOrder);
   
    CreateBorders();
}

void Level::Load()
{
    if (loaded) return;

    LoadBorders();
    LoadField();

    CreateAndLoadSnake();
    SpawnApples();

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

    std::unique_ptr<TileSpriteRenderer> topLeftCornerSpriteRenderer = std::make_unique<TileSpriteRenderer>(topLeftCornerSprite, tileSize, 3, true);
    std::shared_ptr<Border> topLeftCorner = std::make_shared<Border>(std::move(topLeftCornerSpriteRenderer));
    topLeftCorner->position = Vector2D(0, field->Position().Y());

    std::unique_ptr<TileSpriteRenderer> topRightCornerSpriteRenderer = std::make_unique<TileSpriteRenderer>(topRightCornerSprite, tileSize, 3, true);
    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(std::move(topRightCornerSpriteRenderer));
    topRightCorner->position = Vector2D(tileSize + field->Width() * tileSize, field->Position().Y());

    std::unique_ptr<TileSpriteRenderer> bottomLeftCornerSpriteRenderer = std::make_unique<TileSpriteRenderer>(bottomLeftCornerSprite, tileSize, 3, true);
    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(std::move(bottomLeftCornerSpriteRenderer));
    bottomLeftCorner->position = Vector2D(0, field->Position().Y() + tileSize + field->Height() * tileSize);

    std::unique_ptr<TileSpriteRenderer> bottomRightCornerSpriteRenderer = std::make_unique<TileSpriteRenderer>(bottomRightCornerSprite, tileSize, 3, true);
    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(std::move(bottomRightCornerSpriteRenderer));
    bottomRightCorner->position = Vector2D(tileSize + field->Width() * tileSize, field->Position().Y() + tileSize + field->Height() * tileSize);

    borderTiles.push_back(topLeftCorner);
    borderTiles.push_back(topRightCorner);
    borderTiles.push_back(bottomLeftCorner);
    borderTiles.push_back(bottomRightCorner);

    for (int i = 0; i < field->Width(); i++)
    {
        std::unique_ptr<TileSpriteRenderer> topBorderSpriteRenderer = std::make_unique<TileSpriteRenderer>(topBorderSprite, tileSize, 3, true);
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(std::move(topBorderSpriteRenderer));
        topBorder->position = Vector2D(position.X() + tileSize + i * tileSize, position.Y());

        std::unique_ptr<TileSpriteRenderer> bottomBorderSpriteRenderer = std::make_unique<TileSpriteRenderer>(bottomBorderSprite, tileSize, 3, true);
        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(std::move(bottomBorderSpriteRenderer));
        bottomBorder->position = Vector2D(position.X() + tileSize + i * tileSize, position.Y() + tileSize + field->Height() * tileSize);

        borderTiles.push_back(topBorder);
        borderTiles.push_back(bottomBorder);
    }

    for (int i = 0; i < field->Height(); i++)
    {
        std::unique_ptr<TileSpriteRenderer> leftBorderSpriteRenderer = std::make_unique<TileSpriteRenderer>(leftBorderSprite, tileSize, 3, true);
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(std::move(leftBorderSpriteRenderer));
        leftBorder->position = Vector2D(position.X(), position.Y() + tileSize + i * tileSize);

        std::unique_ptr<TileSpriteRenderer> rightBorderSpriteRenderer = std::make_unique<TileSpriteRenderer>(rightBorderSprite, tileSize, 3, true);
        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(std::move(rightBorderSpriteRenderer));
        rightBorder->position = Vector2D(position.X() + tileSize + field->Width() * tileSize, position.Y() + tileSize + i * tileSize);

        borderTiles.push_back(leftBorder);
        borderTiles.push_back(rightBorder);
    } 
}

void Level::CreateAndLoadSnake()
{
    Vector2D snakePosition(tileSize * field->Width() / 2, tileSize * field->Height() / 2);

    std::unique_ptr<TileSpriteRenderer> snakeSpriteRenderer = std::make_unique<TileSpriteRenderer>(nullptr, tileSize, 2, true);

    snake = std::make_shared<Snake>(std::move(snakeSpriteRenderer), snakePosition, Vector2D::Right());
    snake->OnAppleEaten.connect(boost::bind(&Level::AppleEaten, this, boost::placeholders::_1));
    snake->OnSnakeDead.connect(boost::bind(&Level::ShowPlayAgain, this));
    snake->OnSnakeMoved.connect(boost::bind(&Level::FreeSnakeTakenPosition, this, boost::placeholders::_1));
    Engine::AddObject(snake);

    for (const SnakeSegment* segment : snake->GetSegments())
    {
        field->TakePosition(segment->position);
    }    
}

void Level::LoadBorders()
{
    for (std::shared_ptr<Border> object : borderTiles)
    {
        Engine::AddObject(object);
    }
}

void Level::LoadField()
{
    for (std::shared_ptr<GameObject> grass : field->GetFieldTiles())
    {
        Engine::AddObject(grass);
    }
}

void Level::FreeSnakeTakenPosition(Vector2D prevTailPosition)
{
    field->ReleasePosition(prevTailPosition);
    field->TakePosition(snake->position);
}

void Level::ShowPlayAgain()
{
    GameOver();
}

void Level::SpawnApples()
{
    while (appleStorage.CanContainApple() && field->GetFreePositions().size() > 0)
    {
        std::shared_ptr<Apple> newApple = appleSpawner->SpawnApple(field->GetFreePositions());
        appleStorage.AddApple(newApple);
        field->TakePosition(newApple->position);
    }
}

void Level::AppleEaten(Vector2D position)
{
    appleStorage.RemoveAppleAtPosition(position);

    score++;
    ScoreChanged(score);

    SpawnApples();

}

void Level::Reload()
{
    snake->Destroy();
    appleStorage.RemoveAllApples();
    
    field->ReleaseAllPositions();

    CreateAndLoadSnake();

    score = 0;
    ScoreChanged(score);

    SpawnApples();
}