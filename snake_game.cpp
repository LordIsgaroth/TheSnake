#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Start()
{
    mainWindow = new GameWindow("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);
    //GameWindow _secondWindow("The Snake - main menu", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    renderer = new Renderer(mainWindow);
    eventHandler = new EventHandler();
    keyboardListener = new KeyboardListener();

    eventHandler->AddQuitEventListener(this);
    eventHandler->AddKeyboardEventListener(keyboardListener);

    snake = std::make_shared<Snake>();

    std::shared_ptr<Sprite> headSp = renderer->CreateSprite("Graphics/head_up.png");

    snake->posX = (SCREEN_WIDTH - headSp->Width()) / 2;
    snake->posY = (SCREEN_HEIGHT - headSp->Height()) / 2;

    step = headSp->Height();

    snake->SetSprite(headSp);

    renderer->AddToRendering(snake);

    MainLoop();
}

bool SnakeGame::Init()
{
    bool success = true;

    // if (SDL_Init(SDL_INIT_VIDEO) < 0)
    // {
    //     printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    //     success = false;
    // }
    // else
    // {
    //     mainWindow = SDL_CreateWindow("The Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    //     if (mainWindow == nullptr)
    //     {
    //         printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    //         success = false;
    //     }
    //     else
    //     {
    //         //Initialize PNG loading
    //         int imgFlags = IMG_INIT_PNG;
    //         if(!(IMG_Init(imgFlags) & imgFlags))
    //         {
    //              printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    //              success = false;
    //         }
    //         else
    //         {
    //             //screenSurface = SDL_GetWindowSurface(mainWindow);
    //         }
    //     }        
    // }

    return success;
}

void SnakeGame::MainLoop()
{
    quit = false;

    std::shared_ptr<KeyboardEvent> currEvent;

    while(!quit)
    {
        eventHandler->CheckEvents();

        currEvent = keyboardListener->GetEvent();

        if(currEvent)
        {
            if(currEvent->eventType == KeyboardEventType::pressed)
            {
                switch (currEvent->key)
                {
                case SDLK_UP:
                {
                    snake->posY -= step;
                    break;
                }
                case SDLK_DOWN:
                {
                    snake->posY += step;
                    break;
                }
                case SDLK_LEFT:
                {
                    snake->posX -= step;
                    break;
                }
                case SDLK_RIGHT:
                {
                    snake->posX += step;
                    break;
                }
                
                default:
                    break;
                }
            }
        }

        renderer->Render();
    }

    Close();
}

void SnakeGame::Update(bool message)
{
    quit = message;
}

void SnakeGame::Quit()
{
    quit = true;
}

void SnakeGame::Close()
{
    free(mainWindow);
    mainWindow = nullptr;
    free(renderer);
    free(eventHandler);
}
