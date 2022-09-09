#pragma once

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <SDL2/SDL.h>

#include <iostream>

#include "my_little_engine/rendering/renderer.hpp"
#include "my_little_engine/physics/collision_manager.hpp"
#include "my_little_engine/events/event_handler.hpp"
#include "my_little_engine/objects/game_object.hpp"
#include "my_little_engine/objects/scene.hpp"

class EventHandler;
class Scene;

class Engine
{
public:
    static void Initialize(std::string name, int startWidth, int startHeight);
    static void Free();

    static std::shared_ptr<Scene> CurrentScene();
    static const Renderer& GetRenderer();

    static void LoadScene(std::shared_ptr<Scene> scene);

    static void AddObject(std::shared_ptr<GameObject> gameObject);
    static void RemoveObject(int id);

    static void Start();
    static void Quit();

private:
    Engine();

    static bool initialized;
    static std::string gameName;
    static SDL_Window* gameWindow;
    static std::shared_ptr<Scene> currentScene;

    static std::vector<std::shared_ptr<GameObject>> objectsToAdd;
    static std::vector<int> objectsToRemove;

    static std::unique_ptr<Renderer> renderer;
    static std::unique_ptr<EventHandler> eventHandler;
    static std::unique_ptr<CollisionManager> collisionManager;

    static void AddToRendering(std::shared_ptr<GameObject> gameObject);
    static void AddCollideable(std::shared_ptr<GameObject> gameObject);

    static void RemoveFromRendering(std::shared_ptr<GameObject> gameObject);
    static void RemoveCollideable(std::shared_ptr<GameObject> gameObject);

    static void MainLoop();

    static void UpdateAll(double elapsedTime);

    static void AddNewObjects();
    static void RemoveObjects();
};