#include "interface.hpp"

void Interface::CreateScoreLabel(Vector2D position)
{
    std::unique_ptr<Text> scoreText = std::make_unique<Text>("Graphics/snake_font.ttf", 40, "Score: 0");
    std::unique_ptr<LabelRenderer> scoreLabelRenderer = std::make_unique<LabelRenderer>(std::move(scoreText), 300, 60, 100, true);

    scoreLabel = std::make_shared<TextObject>("Score text", std::move(scoreLabelRenderer));
    scoreLabel->position = position;
}

void Interface::CreateGameOverLabel(Vector2D position)
{
    std::unique_ptr<Text> gameOverText = std::make_unique<Text>("Graphics/snake_font.ttf", 45, "Game over!");
    std::unique_ptr<LabelRenderer> gameOverLabelRenderer = std::make_unique<LabelRenderer>(std::move(gameOverText), 400, 100, 100, false);

    gameOverLabel = std::make_shared<TextObject>("Game over text", std::move(gameOverLabelRenderer));
    gameOverLabel->position = position;
}

void Interface::CreatePlayAgainButton(int tileSize, int fieldWidth, int fieldHeight)
{
    std::shared_ptr<Sprite> buttonSprite = std::make_shared<Sprite>("Graphics/button.png");
    std::unique_ptr<SpriteRenderer> buttonSpriteRenderer = std::make_unique<SpriteRenderer>(buttonSprite, 90, false);

    playAgainButton = std::make_shared<Button>("Play again", std::move(buttonSpriteRenderer));

    int posX = (tileSize * 2 + tileSize * fieldWidth - buttonSprite->GetSurface().w) / 2;
    int posY = (tileSize * 4 + tileSize * fieldHeight - buttonSprite->GetSurface().h / 2) / 2;

    playAgainButton->position = Vector2D(posX, posY);
    playAgainButton->OnPressed.connect(boost::bind(&Interface::PlayAgain, this));

    std::unique_ptr<Text> playAgainText = std::make_unique<Text>("Graphics/snake_font.ttf", 35, "Play again?");
    std::unique_ptr<LabelRenderer> playAgainLabelRenderer = std::make_unique<LabelRenderer>(std::move(playAgainText), 260, 50, 100, false);

    playAgainLabel = std::make_shared<TextObject>("Score text", std::move(playAgainLabelRenderer));
    playAgainLabel->position = Vector2D(posX + 20, posY + 23);
}

void Interface::Load()
{
    if (loaded) return;

    Engine::AddObject(scoreLabel);
    Engine::AddObject(gameOverLabel);
    Engine::AddObject(playAgainLabel);
    Engine::AddObject(playAgainButton);

    loaded = true;
}

void Interface::UpdateScore(int score)
{
    scoreLabel->SetText("Score: " + std::to_string(score));    
}

void Interface::ShowPlayAgain()
{
    gameOverLabel->GetTextureRenderer().visible = true;
    playAgainButton->GetSpriteRenderer().visible = true;
    playAgainLabel->GetTextureRenderer().visible = true;
}

void Interface::HidePlayAgain()
{
    gameOverLabel->GetTextureRenderer().visible = false;
    playAgainButton->GetSpriteRenderer().visible = false;
    playAgainLabel->GetTextureRenderer().visible = false;
}

void Interface::PlayAgain()
{
    HidePlayAgain();
    PlayAgainPressed();
}