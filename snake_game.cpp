#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Start()
{
    mainWindow = std::make_shared<GameWindow>("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);
    //GameWindow _secondWindow("The Snake - main menu", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    renderer = new Renderer(mainWindow);
    eventHandler = new EventHandler();

    eventHandler->AddQuitEventListener(mainWindow); 

    apple = std::make_shared<Apple>(renderer->CreateSprite("Graphics/apple.png"));
    //apple->SetSprite(renderer->CreateSprite("Graphics/apple.png"));

    apple->posX = 100;
    apple->posY = 100;

    std::unique_ptr<SnakeHeadSprites> headSprites = std::make_unique<SnakeHeadSprites>();
    headSprites->headUp = renderer->CreateSprite("Graphics/head_up.png");
    headSprites->headDown = renderer->CreateSprite("Graphics/head_down.png");
    headSprites->headRight = renderer->CreateSprite("Graphics/head_right.png");
    headSprites->headLeft = renderer->CreateSprite("Graphics/head_left.png");

    snake = std::make_shared<Snake>(std::move(headSprites));

    snake->posX = (SCREEN_WIDTH - snake->GetSprite()->Width()) / 2;
    snake->posY = (SCREEN_HEIGHT - snake->GetSprite()->Height()) / 2;

    apple->game = this; //testing - remove

    eventHandler->AddKeyboardEventListener(snake);

    AddGameObject(snake);
    AddGameObject(apple);

    //renderer->AddToRendering(apple);
    //renderer->AddToRendering(snake);

    collisionManager.AddCollideable(snake);
    collisionManager.AddCollideable(apple);

    MainLoop();
}

void SnakeGame::MainLoop()
{
    quit = false;

    std::chrono::duration<double> elapsed_seconds;

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();

    while(!quit)
    {
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() * 1000 << std::endl;

        start = std::chrono::system_clock::now();
 
        eventHandler->CheckEvents();

        UpdateAll(elapsed_seconds.count() * 1000); //msec
        //snake->Update(elapsed_seconds.count() * 1000); //msec
        
        collisionManager.CheckCollisions();

        renderer->Render();

        Remove();

        quit = !mainWindow->IsActive();

        end = std::chrono::system_clock::now();
    }

    Close();
}

void SnakeGame::Quit()
{
    quit = true;
}

void SnakeGame::AddGameObject(std::shared_ptr<GameObject> object)
{
    auto objInSet = gameObjects.find(object);

    if (objInSet == gameObjects.end())
    {
        gameObjects.insert(object);
    }

    if (object->IsDrawable()) renderer->AddToRendering(object);
}

void SnakeGame::RemoveGameObject(std::shared_ptr<GameObject> object)
{
    auto objInSet = gameObjects.find(object);

    if (objInSet != gameObjects.end())
    {
        gameObjects.erase(*objInSet);
    }

    if (object->IsDrawable()) renderer->RemoveFromRendering(object);
}

void SnakeGame::Remove()
{
    //TODO: structure for objects to remove 

    if (objectsToRemove.size() > 0)
    {
        collisionManager.RemoveCollideable(apple);
        RemoveGameObject(apple);
    }

    objectsToRemove.clear();
}

void SnakeGame::UpdateAll(double elapsedTime)
{
    for (std::shared_ptr<GameObject> obj : gameObjects)
    {
        obj->Update(elapsedTime);
    }
}

void SnakeGame::DeleteCollideable()
{
    //For testing. TODO - make universal
    objectsToRemove.insert(apple);

        
}

void SnakeGame::Close()
{   
    //mainWindow->~GameWindow();
    //free(mainWindow);
    mainWindow = nullptr;
    free(renderer);
    free(eventHandler);
}
