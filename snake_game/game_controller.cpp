 #include "game_controller.hpp"

GameController::GameController(int tileSize, int fieldWidth, int fieldHeight, int minApplesCount)
{
    scoreFieldSize = 2 * tileSize;

    name = "Game controller";
    //currentApplesCount = 0;
    score = 0;

    this->tileSize = tileSize;
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;

    int applesRenderingOrder = 1;

    field = std::make_shared<Field>(Vector2D(0, scoreFieldSize), tileSize, fieldWidth, fieldHeight);
    appleSpawner = std::make_shared<AppleSpawner>(minApplesCount, tileSize, applesRenderingOrder);

    CreateTexts();
}

void GameController::CreateTexts()
{
    std::unique_ptr<Text> scoreText = std::make_unique<Text>("Graphics/snake_font.ttf", 40, "Score: 0");
    std::unique_ptr<Text> gameOverText = std::make_unique<Text>("Graphics/snake_font.ttf", 45, "Game over!");
    
    std::unique_ptr<LabelRenderer> scoreLabelRenderer = std::make_unique<LabelRenderer>(std::move(scoreText), 300, 60, 100, true);
    std::unique_ptr<LabelRenderer> gameOverLabelRenderer = std::make_unique<LabelRenderer>(std::move(gameOverText), 400, 100, 100, false);

    scoreLabel = std::make_shared<TextObject>("Score text", std::move(scoreLabelRenderer));
    scoreLabel->position = Vector2D(((2 * tileSize + fieldWidth * tileSize) / 2) - 150, 0);

    gameOverLabel = std::make_shared<TextObject>("Game over text", std::move(gameOverLabelRenderer));
    gameOverLabel->position = Vector2D(((2 * tileSize + fieldWidth * tileSize) / 2) - 200, 200);
}

void GameController::CreateSnake()
{
    Vector2D snakePosition(tileSize * fieldWidth / 2, tileSize * fieldHeight / 2);

    snake = std::make_shared<Snake>(CreateTileSpriteRenderer(nullptr, 2), snakePosition, Vector2D::Right());
    snake->OnAppleEaten.connect(boost::bind(&GameController::AppleEaten, this));
    snake->OnSnakeDead.connect(boost::bind(&GameController::ShowPlayAgain, this));
    Engine::AddObject(snake);
}

void GameController::CreatePlayAgainButton()
{
    std::shared_ptr<Sprite> buttonSprite = std::make_shared<Sprite>("Graphics/button.png");
    std::unique_ptr<SpriteRenderer> buttonSpriteRenderer = std::make_unique<SpriteRenderer>(buttonSprite, 90, false);

    playAgainButton = std::make_shared<Button>("Play again", std::move(buttonSpriteRenderer));

    std::cout << buttonSprite->GetSurface().w << std::endl;
    std::cout << buttonSprite->GetSurface().h << std::endl;

    int posX = (tileSize * 2 + tileSize * fieldWidth - buttonSprite->GetSurface().w) / 2;
    int posY = (tileSize * 4 + tileSize * fieldHeight - buttonSprite->GetSurface().h / 2) / 2;

    playAgainButton->position = Vector2D(posX, posY);
    playAgainButton->OnPressed.connect(boost::bind(&GameController::PlayAgain, this));

    std::unique_ptr<Text> playAgainText = std::make_unique<Text>("Graphics/snake_font.ttf", 35, "Play again?");
    std::unique_ptr<LabelRenderer> playAgainLabelRenderer = std::make_unique<LabelRenderer>(std::move(playAgainText), 260, 50, 100, false);

    playAgainLabel = std::make_shared<TextObject>("Score text", std::move(playAgainLabelRenderer));
    playAgainLabel->position = Vector2D(posX + 20, posY + 23);

    Engine::AddObject(playAgainButton);
    Engine::AddObject(playAgainLabel);    
}

void GameController::ShowPlayAgain()
{
    gameOverLabel->GetTextureRenderer().visible = true;

    if(!playAgainButton) CreatePlayAgainButton();
    playAgainButton->GetSpriteRenderer().visible = true;
    playAgainLabel->GetTextureRenderer().visible = true;
}

std::unique_ptr<SpriteRenderer> GameController::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder, true));
}

void GameController::Update(double elapsedTime)
{
    appleSpawner->SpawnApples(field->GetFreePositions());
    
    movementDuration += elapsedTime;

    if (movementDuration >= maxMovementDuration)
    {
        movementDuration = 0;
        snake->Move(); 
    }

    //std::cout << movementDuration << std::endl;
}

void GameController::AppleEaten()
{
    appleSpawner->ReduceCurrentApplesCount();
    appleSpawner->SpawnApples(field->GetFreePositions());

    score++;
    UpdateScore();
}

void GameController::UpdateScore()
{
    scoreLabel->SetText("Score: " + std::to_string(score));
}

void GameController::PlayAgain()
{
    snake->Destroy();

    gameOverLabel->GetTextureRenderer().visible = false;
    playAgainButton->GetSpriteRenderer().visible = false;
    playAgainLabel->GetTextureRenderer().visible = false;

    CreateSnake();

    score = 0;
    UpdateScore();

    // Engine::RemoveObject(apple->Id());
    // currentApplesCount--;

    // AddApple();
}