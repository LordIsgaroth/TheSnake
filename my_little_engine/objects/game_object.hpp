#pragma once

#include <memory>
#include "../rendering/sprite.hpp"

class GameObject
{
public:
    virtual void Update(double elapsedTime) = 0;

    bool IsDrawable();
    void SetSprite(std::shared_ptr<Sprite>);
    std::shared_ptr<Sprite> GetSprite();

    //TODO: make specific class for position
    double posX = 0;
    double posY = 0;

private:
    std::shared_ptr<Sprite> sprite = nullptr;    
};