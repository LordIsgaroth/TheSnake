#include "snake_game.hpp"

SnakeGame::SnakeGame() {}

void SnakeGame::Start()
{
    mainWindow = new GameWindow("The Snake", SCREEN_WIDTH, SCREEN_HEIGHT);
    //GameWindow _secondWindow("The Snake - main menu", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    renderer = new Renderer(mainWindow);

    Sprite* headSp = renderer->CreateSprite("Graphics/head_up.png");

    int posX = (SCREEN_WIDTH - headSp->Width()) / 2;
    int posY = (SCREEN_HEIGHT - headSp->Height()) / 2;

    renderer->DrawSprite(headSp, posX, posY);

    //if(!Init()) throw "Init failed!";

    

    //SDL_FillRects(screenSurface, NULL, 1, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    //SDL_UpdateWindowSurface(mainWindow);

    // SDL_Surface *head = IMG_Load("Graphics/head_up.png"); 

    // SDL_Renderer *renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //  SDL_Surface *head = IMG_Load("Graphics/head_up.png"); 

    // if(renderer == nullptr )
    // {
    //     printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );    
    // }

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


    // //SDL_Texture *headTx = IMG_LoadTexture(renderer, "Graphics/head_up.png");

    
    
    // if(renderer == nullptr )
    // {
    //     printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );    
    // }

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // SDL_Texture *headTx = SDL_CreateTextureFromSurface(renderer, head); 

    // if(headTx == nullptr)
    // {
    //     printf( "Unable to create texture! SDL Error: %s\n", SDL_GetError() );
    // }


    // //SDL_Texture *headTx = IMG_LoadTexture(renderer, "Graphics/head_up.png");

    // SDL_Rect rectHead;
    // rectHead.h = head->h;
    // rectHead.w = head->w;
    // rectHead.x = (SCREEN_WIDTH - head->w) / 2;
    // rectHead.y  = (SCREEN_HEIGHT - head->h) / 2;

    // SDL_RenderClear(renderer); //Очистка рендера
    // //SDL_RenderCopy(renderer,background,NULL,&background_RECT); //Копируем в рендер фон
    // SDL_RenderCopy(renderer, headTx, NULL, &rectHead); //Копируем в рендер персонажа
    // SDL_RenderPresent(renderer);

    //SDL_BlitSurface(head, NULL, screenSurface, &rectHead);
    //SDL_UpdateWindowSurface(mainWindow);

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
    bool quit = false;

    SDL_Event event;

    while(!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }

            //Apply the PNG image                                                                                                                                                      
            //SDL_BlitSurface(loadSurface("Graphics/head_up.png"), NULL, screenSurface, NULL);
                                                                                                               
            //Update the surface                                                                                                                                                       
            //SDL_UpdateWindowSurface(mainWindow);

            // else if (event.type == SDL_KEYDOWN)
            // {
            //     switch (event.key.keysym.sym)
            //     {
            //     case SDLK_UP:
            //         currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
			// 		break;

			// 	case SDLK_DOWN:
			// 	    currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
			// 		break;

			// 	case SDLK_LEFT:
			// 		currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
			// 		break;

			// 	case SDLK_RIGHT:
			// 	    currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
			// 		break;

			// 	default:
			// 		currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			// 		break;
            //     }
            // }
            
            // //Apply the current image
			// SDL_BlitSurface(currentSurface, NULL, gScreenSurface, NULL);
			
			//Update the surface
			//SDL_UpdateWindowSurface( gWindow );
        }
    }

    Close();
}

void SnakeGame::Close()
{
    free(mainWindow);
    mainWindow = nullptr;

    SDL_Quit();
}

// SDL_Surface* SnakeGame::loadSurface(std::string path)
// {
//     //The final optimized image
//     SDL_Surface* optimizedSurface = NULL;

//     //Load image at specified path
//     SDL_Surface* loadedSurface = IMG_Load(path.c_str());

//     if(loadedSurface == NULL)
//     {
//         printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//     }
//     else
//     {
//         //Convert surface to screen format
//         optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);

//         if (optimizedSurface == NULL)
//         {
//             printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//         }

//         //Get rid of old loaded surface
//         SDL_FreeSurface(loadedSurface);
//     }

//     return optimizedSurface;
// }