#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "snake_game_objects.hpp"
#include "field.hpp"
#include "apple_spawner.hpp"
#include "apple_storage.hpp"

//Ответственности класса
//Создание и хранение игровых объектов
//Загрузка игровых объектов в движок
//Управление начислеием очков
//Управление перезапуском игры

class Level : public SceneObject
{
public:
    Level(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount);

    boost::signals2::signal<void(int)> ScoreChanged;
    boost::signals2::signal<void()> GameOver;

    void Load();
    void Reload();

private:
    bool loaded;

    int score = 0;

    int fieldWidth, fieldHeight;
    int tileSize;
    //int minApplesCount;
    int scoreFieldSize;

    std::shared_ptr<Field> field;
    std::shared_ptr<AppleSpawner> appleSpawner;
    AppleStorage appleStorage;

    std::vector<std::shared_ptr<Border>> borderTiles;
    std::shared_ptr<Snake> snake;
   
    void Update(double elapsedTime) override;

    void CreateBorders();
    void CreateAndLoadSnake();

    void LoadBorders();
    void LoadField();

    void AppleEaten(Vector2D position);
    void SpawnApples();
    void ShowPlayAgain();

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder);
};