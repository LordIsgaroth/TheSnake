#include "field.hpp"
#include "snake_game_objects.hpp"

Field::Field(Vector2D position, int tileSize, int width, int height)
{
    this->position = position;
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;

    CreateGrass();
    CreateBorders();
}

void Field::CreateGrass()
{
    std::shared_ptr<Sprite> grassSprite = std::make_shared<Sprite>("Graphics/grass.png");

    for (int i = 0; i < width * height; i++)
    {
        std::shared_ptr<Grass> grass = std::make_shared<Grass>(CreateTileSpriteRenderer(grassSprite, 0));
        int x = tileSize + (i % width) * tileSize;
        int y = position.Y() + tileSize + (i / width) * tileSize;

        Vector2D position = Vector2D(x, y);

        grass->position = Vector2D(x, y);

        tilePositions.push_back(position);
        fieldTiles.push_back(grass);
    }
}

void Field::CreateBorders()
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
    topLeftCorner->position = Vector2D(0, position.Y());

    std::shared_ptr<Border> topRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(topRightCornerSprite, 3));
    topRightCorner->position = Vector2D(tileSize + width * tileSize, position.Y());

    std::shared_ptr<Border> bottomLeftCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomLeftCornerSprite, 3));
    bottomLeftCorner->position = Vector2D(0, position.Y() + tileSize + height * tileSize);

    std::shared_ptr<Border> bottomRightCorner = std::make_shared<Border>(CreateTileSpriteRenderer(bottomRightCornerSprite, 3));
    bottomRightCorner->position = Vector2D(tileSize + width * tileSize, position.Y() + tileSize + height * tileSize);

    borderTiles.push_back(topLeftCorner);
    borderTiles.push_back(topRightCorner);
    borderTiles.push_back(bottomLeftCorner);
    borderTiles.push_back(bottomRightCorner);

    for (int i = 0; i < width; i++)
    {
        std::shared_ptr<Border> topBorder = std::make_shared<Border>(CreateTileSpriteRenderer(topBorderSprite, 3));
        topBorder->position = Vector2D(tileSize + i * tileSize, position.Y());

        std::shared_ptr<Border> bottomBorder = std::make_shared<Border>(CreateTileSpriteRenderer(bottomBorderSprite, 3));
        bottomBorder->position = Vector2D(tileSize + i * tileSize, position.Y() + tileSize + height * tileSize);

        borderTiles.push_back(topBorder);
        borderTiles.push_back(bottomBorder);
    }

    for (int i = 0; i < height; i++)
    {
        std::shared_ptr<Border> leftBorder = std::make_shared<Border>(CreateTileSpriteRenderer(leftBorderSprite, 3));
        leftBorder->position = Vector2D(0, position.Y() + tileSize + i * tileSize);

        std::shared_ptr<Border> rightBorder = std::make_shared<Border>(CreateTileSpriteRenderer(rightBorderSprite, 3));
        rightBorder->position = Vector2D(tileSize + width * tileSize, position.Y() + tileSize + i * tileSize);

        borderTiles.push_back(leftBorder);
        borderTiles.push_back(rightBorder);
    } 
}

void Field::DefineFreePositions()
{
    freeTilePositions.clear();

    for (Vector2D position : tilePositions)
    {
        freeTilePositions.push_back(position);
    }

    // for (SnakeSegment* segment : snake->GetSegments())
    // {
    //     auto pos = std::find(freePositions.begin(), freePositions.end(), segment->position); 

    //     if(pos != freePositions.end())
    //     {
    //         freePositions.erase(pos);
    //     }
    // }
}

Vector2D Field::GetRandomFreePosition()
{
    std::srand(std::time(nullptr));
    DefineFreePositions();

    Vector2D newPosition = freeTilePositions[std::rand() % (freeTilePositions.size() - 1)];
    
    //std::cout << "new apple position (x): " << newPosition.X() << std::endl;
    //std::cout << "new apple position (y): " << newPosition.Y() << std::endl;

    return newPosition;
}

std::unique_ptr<SpriteRenderer> Field::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder, true));
}