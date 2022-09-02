#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "my_little_engine/core/engine.hpp"
#include "game_object.hpp"

class Engine;

class Scene
{
    friend class Engine;

public:
    Scene(std::string name);
    Scene(std::string name, std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading);

    const std::string& Name();
    const std::unordered_map<int, std::shared_ptr<GameObject>>& GameObjects();
    bool Active() const;
    void Close();

    bool ContainsObject(int id) const;
    
private:
    std::string name;
    std::unordered_map<int, std::shared_ptr<GameObject>> gameObjects;
    bool active = true;

    void AddObject(std::shared_ptr<GameObject> gameObject);
    void RemoveObject(int id);
};