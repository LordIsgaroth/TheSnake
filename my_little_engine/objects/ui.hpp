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
    void Input(std::shared_ptr<KeyboardEvent> inputEvent) override;

    bool IsDrawable() const override { return spriteRenderer != nullptr; }
    TextureRenderer& GetTextureRenderer() const override { return *spriteRenderer; }
    SpriteRenderer& GetSpriteRenderer() const { return *spriteRenderer; }

protected:
    std::unique_ptr<SpriteRenderer> spriteRenderer;
};