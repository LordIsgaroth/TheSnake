#include "engine.hpp"

bool Engine::initialized;
std::string Engine::gameName;
std::shared_ptr<Scene> Engine::currentScene;

std::vector<std::shared_ptr<GameObject>> Engine::objectsToAdd;
std::vector<int> Engine::objectsToRemove;

SDL_Window* Engine::gameWindow;
std::unique_ptr<Renderer> Engine::renderer;
std::unique_ptr<EventHandler> Engine::eventHandler;
std::unique_ptr<CollisionManager> Engine::collisionManager;

void Engine::Initialize(std::string name, int startWidth, int startHeight)
{
    if (initialized) return;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw SDL_GetError();
    }

    initialized = true;
    gameName = name;

    gameWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, startWidth, startHeight, SDL_WINDOW_SHOWN);
    renderer = std::make_unique<Renderer>(gameWindow);

    eventHandler = std::make_unique<EventHandler>();
    collisionManager = std::make_unique<CollisionManager>();  
}

void Engine::Free()
{
    if(!initialized) return;

    initialized = false;
    gameName = "";

    SDL_DestroyWindow(gameWindow);

    renderer = nullptr;
    eventHandler = nullptr;
    collisionManager = nullptr;

    SDL_Quit();
}

std::shared_ptr<Scene> Engine::CurrentScene() { return currentScene; }

const Renderer& Engine::GetRenderer()
{
    return *renderer;
}

void Engine::LoadScene(std::shared_ptr<Scene> scene)
{   
    currentScene = scene;

    for (auto record : scene->GameObjects())
    {
        if (record.second->HandlesInput()) eventHandler->AddInputEventListener(record.second);
        AddToRendering(record.second);
        AddCollideable(record.second);
    }    
}

void Engine::AddObject(std::shared_ptr<GameObject> gameObject)
{
    if (!initialized) throw ("Engine not initialized!");
    if (!currentScene) throw ("Scene not loaded!");

    if (!currentScene->ContainsObject(gameObject->Id())) objectsToAdd.push_back(gameObject);
}

void Engine::RemoveObject(int id)
{
    if (!initialized) throw ("Engine not initialized!");
    if (!currentScene) throw ("Scene not loaded!");

    if (currentScene->ContainsObject(id)) objectsToRemove.push_back(id);
}

void Engine::AddToRendering(std::shared_ptr<GameObject> gameObject)
{
    if (gameObject->IsDrawable()) renderer->AddToRendering(gameObject);
}

void Engine::AddCollideable(std::shared_ptr<GameObject> gameObject)
{
    std::shared_ptr<CollisionObject> collObj = std::dynamic_pointer_cast<CollisionObject>(gameObject);        
    if (collObj) collisionManager->AddCollideable(collObj);
}

void Engine::RemoveFromRendering(std::shared_ptr<GameObject> gameObject)
{
    if(gameObject->IsDrawable()) renderer->RemoveFromRendering(gameObject->Id(), gameObject->GetSpriteRenderer()->RenderingOrder());
}

void Engine::RemoveCollideable(std::shared_ptr<GameObject> gameObject)
{
    std::shared_ptr<CollisionObject> collObj = std::dynamic_pointer_cast<CollisionObject>(gameObject);        
    if (collObj) collisionManager->RemoveCollideable(collObj->Id());
}

void Engine::Start()
{
    MainLoop();
}

void Engine::Quit()
{
    if(currentScene) currentScene->Close();
}

void Engine::MainLoop()
{
    std::chrono::duration<double> elapsed_seconds;

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();

    while(currentScene->Active())
    {
        elapsed_seconds = end - start;
        //std::cout << elapsed_seconds.count() * 1000 << std::endl;

        start = std::chrono::system_clock::now();
 
        AddNewObjects();

        eventHandler->CheckEvents();
        collisionManager->CheckCollisions();

        UpdateAll(elapsed_seconds.count() * 1000); //msec
        
        renderer->Render();

        RemoveObjects();

        end = std::chrono::system_clock::now();
    }
}

void Engine::UpdateAll(double elapsedTime)
{
    for (auto record : currentScene->GameObjects())
    {
        record.second->Update(elapsedTime);
    }
}

void Engine::AddNewObjects()
{
    for(std::shared_ptr<GameObject> gameObject : objectsToAdd)
    {
        if(currentScene->ContainsObject(gameObject->Id())) continue;

        currentScene->AddObject(gameObject);

        if(gameObject->HandlesInput()) eventHandler->AddInputEventListener(gameObject);

        AddToRendering(gameObject);
        AddCollideable(gameObject);
    }

    objectsToAdd.clear();
}

void Engine::RemoveObjects()
{
    for(int id : objectsToRemove)
    {
        if(!currentScene->ContainsObject(id)) continue;

        std::shared_ptr<GameObject> objToRemove = currentScene->GameObjects().find(id)->second;
        currentScene->RemoveObject(id);

        if(objToRemove->HandlesInput()) eventHandler->RemoveInputEventListener(objToRemove);

        RemoveFromRendering(objToRemove);
        RemoveCollideable(objToRemove);   
    }

    objectsToRemove.clear();
}