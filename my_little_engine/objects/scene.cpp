#include "scene.hpp"

Scene::Scene(std::string name)
{
    this->name = name;
}

Scene::Scene(std::string name, std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> objectsForLoading)
{
    this->name = name;

    for (std::shared_ptr<GameObject> gameObject : *objectsForLoading)
    {
        gameObjects.insert(std::make_pair(gameObject->Id(), gameObject));
    }
}

const std::string& Scene::Name()
{
    return name;
}

const std::unordered_map<int, std::shared_ptr<GameObject>>& Scene::GameObjects()
{
    return gameObjects;
}

bool Scene::Active() const
{
    return active;
}

void Scene::Close() { active = false; }

bool Scene::ContainsObject(int id) const
{
    if (gameObjects.find(id) != gameObjects.end()) return true;
    else return false;
}

void Scene::AddObject(std::shared_ptr<GameObject> gameObject)
{
    if(ContainsObject(gameObject->Id())) return;
    gameObjects.insert(std::make_pair(gameObject->Id(), gameObject));
}

void Scene::RemoveObject(int id)
{
    if(!ContainsObject(id)) return;
    gameObjects.erase(id);
}