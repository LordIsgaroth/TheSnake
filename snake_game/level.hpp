#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "my_little_engine/my_little_engine.hpp"

#include "tile_sprite_renderer.hpp"
#include "snake.hpp"
#include "snake_game_objects.hpp"
#include "field.hpp"
#include "apple_spawner.hpp"
#include "apple_storage.hpp"

class Level
{
public:
    Level(Vector2D postion, int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);

    boost::signals2::signal<void(int)> ScoreChanged;
    boost::signals2::signal<void()> GameOver;

    void Load();
    void Reload();

private:
    bool loaded;

    int score = 0;

    Vector2D position;
    int tileSize;
   
    std::shared_ptr<Field> field;
    std::shared_ptr<AppleSpawner> appleSpawner;
    AppleStorage appleStorage;

    std::vector<std::shared_ptr<Border>> borderTiles;
    std::shared_ptr<Snake> snake;
  
    void CreateBorders();
    void CreateAndLoadSnake();

    void LoadBorders();
    void LoadField();
    void FreeSnakeTakenPosition(Vector2D prevTailPosition);

    void AppleEaten(Vector2D position);
    void SpawnApples();
    void ShowPlayAgain();
};