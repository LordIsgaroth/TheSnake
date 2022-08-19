#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <chrono>
#include <iostream>

#include "my_little_engine.hpp"

#include "snake.hpp"
#include "apple.hpp"

class Apple;

class SnakeGame
{
public:
    SnakeGame();
    void Start();
    void DeleteCollideable();

private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    std::shared_ptr<GameWindow> mainWindow;
    Renderer* renderer = nullptr;
    EventHandler* eventHandler;
    CollisionManager collisionManager;

    std::shared_ptr<Snake> snake;
    std::shared_ptr<Apple> apple; 

    bool quit = false;

    void AddGameObject(std::shared_ptr<GameObject> object);
    void RemoveGameObject(std::shared_ptr<GameObject> object);

    std::unordered_set<std::shared_ptr<GameObject>> gameObjects;
    std::unordered_set<std::shared_ptr<GameObject>> objectsToRemove;

    void MainLoop();
    void UpdateAll(double elapsedTime);
    void Remove();
    void Quit();
    void Close();


};