#pragma once

#include "game_object.hpp"

//testing
#include <iostream>

// class InterfaceObject : public GameObject
// {
    

// };

class Button : public GameObject
{
public:
    Button(std::string buttonName, std::unique_ptr<SpriteRenderer> spriteRenderer);

    void Update(double elapsedTime) override {}
    void Input(std::shared_ptr<SDL_Event> inputEvent) override;

    bool IsDrawable() const override { return spriteRenderer != nullptr; }
    TextureRenderer& GetTextureRenderer() const override { return *spriteRenderer; }
    SpriteRenderer& GetSpriteRenderer() const { return *spriteRenderer; }

protected:
    std::unique_ptr<SpriteRenderer> spriteRenderer;

    //В дальнейшем вывести в какой-либо общий класс
    bool PointInRect(Vector2D point, Vector2D rectPosition, const SDL_Rect& rect);  
};